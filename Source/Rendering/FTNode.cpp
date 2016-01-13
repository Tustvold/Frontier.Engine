#include <Rendering/FTNode.h>
#include <Util/FTMath.h>
#include <Rendering/Camera/FTCamera.h>
#include <Rendering/FTDirector.h>
#include "Action/FTActionManager.h"
#include <Rendering/FTView.h>
#include <Event/Input/FTInputManager.h>

FTNode::FTNode() :
                   flags_(InitialFlags),
                   rotation_transform_(new FTTransformRotation),
                   position_transform_(new FTTransformPosition()),
                   scale_transform_(new FTTransformScale()),
                   model_matrix_inv_dirty_(true),
                   parent_(nullptr),
                   view_(nullptr),
                   scene_(nullptr) {

}

FTNode::~FTNode() {
    if (flags_ & MouseInputEnabled)
        FTEngine::getInputManager()->removeMouseDelegate(this);

}

void FTNode::setMouseInputEnabled(bool enabled) {
    if (enabled == ((flags_ & MouseInputEnabled) != 0))
        return;
    if (enabled) {
        FTEngine::getInputManager()->addMouseDelegate(this);
        flags_ |= MouseInputEnabled;
    } else {
        FTEngine::getInputManager()->removeMouseDelegate(this);
        flags_ &= ~MouseInputEnabled;
    }
}

bool FTNode::isVisible(FTCamera* camera) {
    return camera->testNodeVisible(this);
}


void FTNode::addChild(const std::shared_ptr<FTNode>& child) {
    FTAssert(child, "Trying to add nullptr as child");
    FTAssert(child->parent_ == nullptr, "Node already has parent");
    FTAssert(child->view_ == nullptr, "Node already has view set");
    child->parent_ = this;
    children_.push_back(child);
    this->setDirty(ChildNodeDirty);
    if (view_)
        child->onAddedToView(view_);
    if (scene_)
        child->onAddedToScene(scene_);
    if (flags_ & IsActive)
        child->onEnter();
}


void FTNode::addChild(std::shared_ptr<FTNode>&& child) {
    FTAssert(child, "Trying to add nullptr as child");
    FTAssert(child->parent_ == nullptr, "Node already has parent");
    FTAssert(child->view_ == nullptr, "Node already has view set");

    auto child_ptr = child.get();
    children_.push_back(std::move(child));
    this->setDirty(ChildNodeDirty);
    child_ptr->parent_ = this;
    if (view_)
        child_ptr->onAddedToView(view_);
    if (scene_)
        child_ptr->onAddedToScene(scene_);
    if (flags_ & IsActive)
        child_ptr->onEnter();
}

bool FTNode::updateMatrices(const glm::mat4& parent_matrix) {
    if (flags_ & TransformDirty) {
        scale_transform_->updateMatrices();
        rotation_transform_->updateMatrices();

        auto rotate_scale_matrix = rotation_transform_->getTransformMatrix() * scale_transform_->getTransformMatrix();
        glm::vec4 offset = glm::vec4(-anchor_point_.x * size_.x, -anchor_point_.y * size_.y, -anchor_point_.z * size_.z, 1);

        auto rotated_scale_offset = rotate_scale_matrix * offset;

        position_transform_->setPosition(glm::vec3(unaltered_position_.x + rotated_scale_offset.x, unaltered_position_.y + rotated_scale_offset.y, unaltered_position_.z + rotated_scale_offset.z));
        position_transform_->updateMatrices();

        transform_matrix_ = position_transform_->getTransformMatrix() * rotate_scale_matrix;
    }

    model_matrix_ = parent_matrix * transform_matrix_;

    flags_ &= ~TransformDirty;
    model_matrix_inv_dirty_ = true;
    return true;
}


void FTNode::visit(const glm::mat4& parent_matrix, bool parent_updated) {
    auto original_dirty = flags_ & DirtyMask;
    if (!parent_updated && original_dirty == 0)
        return;


    if (original_dirty & TransformDirty || parent_updated)
        updateMatrices(parent_matrix);

    for (auto it = children_.begin(); it != children_.end(); ++it) {
        (*it)->visit(model_matrix_, parent_updated || (original_dirty & ~ChildNodeDirty) != 0);
    }

    if (original_dirty & AABDirtyMask || parent_updated)
        updateAAB();

    flags_ &= ~ChildNodeDirty;
}

void FTNode::performDraw(FTCamera* camera) {
    if (getHidden() || (flags_ & FrustrumCullEnabled && !isVisible(camera)))
        return;

    glm::mat4 mvp = camera->getViewProjectionMatrix() * model_matrix_;

    this->pre_draw(mvp);
    this->draw();
    this->post_draw();


    for (auto it = children_.begin(); it != children_.end(); ++it) {
        (*it)->performDraw(camera);
    }
}

void FTNode::updateAAB() {
    auto min = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
    auto max = glm::vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

    const glm::mat4& model_matrix = model_matrix_;

    if (size_ != glm::vec3(0, 0, 0)) {
        glm::vec4 positions[8] = {
            glm::vec4(0, 0, 0, 1),
            glm::vec4(size_.x, 0, 0, 1),
            glm::vec4(0, size_.y, 0, 1),
            glm::vec4(0, 0, size_.z, 1),
            glm::vec4(size_.x, size_.y, 0, 1),
            glm::vec4(size_.x, 0, size_.z, 1),
            glm::vec4(0, size_.y, size_.z, 1),
            glm::vec4(size_.x, size_.y, size_.z, 1)
        };

        for (int i = 0; i < 8; i++) {
            auto transformed = model_matrix * positions[i];
            max.x = FTMAX(transformed.x, max.x);
            max.y = FTMAX(transformed.y, max.y);
            max.z = FTMAX(transformed.z, max.z);

            min.x = FTMIN(transformed.x, min.x);
            min.y = FTMIN(transformed.y, min.y);
            min.z = FTMIN(transformed.z, min.z);
        }
    } else if (children_.size() == 0) {
        flags_ &= ~HasAAB;
        return;
    }
    flags_ |= HasAAB;

    for (auto it = children_.begin(); it != children_.end(); ++it) {
        (*it)->updateAAB();
        auto center = (*it)->getAABCenter();
        auto halfExtents = (*it)->getAABHalfExtents();

        max.x = FTMAX(center.x + halfExtents.x, max.x);
        max.y = FTMAX(center.y + halfExtents.y, max.y);
        max.z = FTMAX(center.z + halfExtents.z, max.z);

        min.x = FTMIN(center.x - halfExtents.x, min.x);
        min.y = FTMIN(center.y - halfExtents.y, min.y);
        min.z = FTMIN(center.z - halfExtents.z, min.z);
    }

    aab_extents_ = (max - min) / 2.0f;
    aab_center_ = (max + min) / 2.0f;
}

void FTNode::runAction(std::unique_ptr<FTAction>&& action) {
    FTEngine::getDirector()->getActionManager()->addAction(this, std::move(action));
}

void FTNode::removeChild(FTNode* node) {
    FTAssert(node->parent_ == this, "Node is not a child of this node")
    auto it = children_.begin();
    for (; it != children_.end(); ++it) {
        if (it->get() == node)
            break;
    }
    FTAssert(it != children_.end(), "Node is not a child of this node");
    if (getIsActive())
        node->onExit();
    if (scene_ != nullptr)
        node->onRemovedFromScene();
    if (view_ != nullptr)
        node->onRemovedFromView();
    node->parent_ = nullptr;

    children_.erase(it);
}

glm::vec3 FTNode::convertMouseToLocalCoordinates(const glm::vec2& mouse_coords) {
    FTAssert(view_ != nullptr, "Node not added to an FTView");

    auto unprojected = view_->getCamera()->unProject(glm::vec3(mouse_coords, 0));

    auto& mat = getModelMatrixInverse();
    glm::vec4 mouse_pos = glm::vec4((float)unprojected.x, (float)unprojected.y, 0, 1);
    glm::vec4 local_pos = mat * mouse_pos;
    return glm::vec3(local_pos.x / local_pos.w, local_pos.y / local_pos.w, local_pos.z / local_pos.w);
}

void FTNode::onAddedToView(FTView* view) {
    FTAssert(view_ == nullptr, "Node already paired with view");
    view_ = view;

    for (auto it = children_.begin(); it != children_.end(); ++it)
        (*it)->onAddedToView(view);
}

void FTNode::onAddedToScene(FTScene* scene) {
    FTAssert(scene_ == nullptr, "Node already paired with scene");
    scene_ = scene;
    for (auto it = children_.begin(); it != children_.end(); ++it)
        (*it)->onAddedToScene(scene);
}

void FTNode::onRemovedFromView() {
    FTAssert(view_ != nullptr, "Node already removed from scene");
    view_ = nullptr;
    for (auto it = children_.begin(); it != children_.end(); ++it)
        (*it)->onRemovedFromView();
}

void FTNode::onRemovedFromScene() {
    FTAssert(scene_ != nullptr, "Node already removed from scene");
    scene_ = nullptr;
    for (auto it = children_.begin(); it != children_.end(); ++it)
        (*it)->onRemovedFromScene();
}

void FTNode::onEnter() {
    flags_ |= IsActive;
    for (auto it = children_.begin(); it != children_.end(); ++it)
        (*it)->onEnter();
}

void FTNode::onExit() {
    flags_ &= ~IsActive;
    for (auto it = children_.begin(); it != children_.end(); ++it)
        (*it)->onExit();
}
