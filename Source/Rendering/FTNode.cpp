#include <Rendering/FTNode.h>
#include <Rendering/Camera/FTCamera.h>
#include <Rendering/FTDirector.h>
#include "Action/FTActionManager.h"
#include <Rendering/FTView.h>

FTNode::FTNode() :
    bounding_shape_(new FTBoundingShape()),
    button_(nullptr),
    flags_(InitialFlags),
    tag_(0),
    rotation_transform_(new FTTransformRotation),
    position_transform_(new FTTransformPosition()),
    scale_transform_(new FTTransformScale()),
    model_matrix_inv_dirty_(true),
    parent_(nullptr),
    view_(nullptr),
    scene_(nullptr) {
    bounding_shape_->onAddedToNode(this);
}

FTNode::~FTNode() {

}

bool FTNode::isVisible(FTCamera* camera) {
    return bounding_shape_->visibleInCamera(camera);
}


void FTNode::addChild(const std::shared_ptr<FTNode>& child) {
    FTAssert(child, "Trying to add nullptr as child");
    FTAssert(child->parent_ == nullptr, "Node already has parent");
    FTAssert(child->view_ == nullptr, "Node already has view set");
    child->parent_ = this;
    children_.push_back(child);
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
    child_ptr->parent_ = this;
    if (view_)
        child_ptr->onAddedToView(view_);
    if (scene_)
        child_ptr->onAddedToScene(scene_);
    if (flags_ & IsActive)
        child_ptr->onEnter();
}

bool FTNode::updateTransformMatrices(const glm::mat4& parent_matrix) {
    if (flags_ & TransformDirty) {
        rotation_transform_->updateMatrices();
        //position_transform_->updateMatrices();
        //scale_transform_->updateMatrices();
        transform_matrix_ = position_transform_->getTransformMatrix() * rotation_transform_->getTransformMatrix() * scale_transform_->getTransformMatrix();;
    }

    if (bounding_shape_->getDirty() || flags_ & AnchorPointDirty) {
        bounding_shape_->updateMatrices();
    }

    model_matrix_ = parent_matrix * transform_matrix_ * bounding_shape_->getAnchorPointTransformMatrix();

    flags_ &= ~TransformDirty;
    model_matrix_inv_dirty_ = true;
    return true;
}


void FTNode::visit(const glm::mat4& parent_matrix, bool parent_updated) {
    draw_order_ = NODE_DRAW_ORDER_INVALID;
    auto original_dirty = flags_ & DirtyMask || bounding_shape_->getDirty() || parent_updated;

    if (original_dirty & TransformDirty || parent_updated || bounding_shape_->getDirty())
        updateTransformMatrices(parent_matrix);

    for (auto it = children_.begin(); it != children_.end(); ++it) {
        (*it)->visit(model_matrix_, original_dirty != 0);
    }

    if (original_dirty & BoundingShapeDirtyMask || parent_updated || bounding_shape_->getDirty())
        bounding_shape_->visit();
}

void FTNode::performDraw(FTCamera* camera, uint32_t& draw_order) {
    if (getHidden())
        return;


    if ((flags_ & FrustrumCullEnabled) == 0 || isVisible(camera)) {
        draw_order_ = draw_order++;
        this->pre_draw(camera);
        this->draw();
        this->post_draw();
    }

    for (auto it = children_.begin(); it != children_.end(); ++it) {
        (*it)->performDraw(camera, draw_order);
    }
}

void FTNode::runAction(std::unique_ptr<FTAction>&& action) {
    FTEngine::getDirector()->getActionManager()->addAction(this, std::move(action));
}

void FTNode::resetAllActions() {
    FTEngine::getDirector()->getActionManager()->resetActionsForNode(this);
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
    draw_order_ = NODE_DRAW_ORDER_INVALID;
    for (auto it = children_.begin(); it != children_.end(); ++it)
        (*it)->onEnter();
}

void FTNode::onExit() {
    flags_ &= ~IsActive;
    draw_order_ = NODE_DRAW_ORDER_INVALID;
    for (auto it = children_.begin(); it != children_.end(); ++it)
        (*it)->onExit();
}

void FTNode::setButtonEnabled(bool enabled) {
    if (enabled) {
        if (button_ == nullptr)
            button_ = std::make_unique<FTButton>(this);
    } else {
        button_.reset();
    }
}

glm::vec3 FTNode::convertMouseToLocalCoordinates(const glm::vec2& mouse_coords) {
    FTAssert(view_ != nullptr, "Node not added to an FTView");

    auto unprojected = view_->getCamera()->unProject(glm::vec3(mouse_coords, 0));

    auto& mat = getModelMatrixInverse();
    glm::vec4 mouse_pos = glm::vec4((float)unprojected.x, (float)unprojected.y, 0, 1);
    glm::vec4 local_pos = mat * mouse_pos;
    return glm::vec3(local_pos.x / local_pos.w, local_pos.y / local_pos.w, local_pos.z / local_pos.w);
}

