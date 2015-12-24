#include <Rendering/FTNode.h>
#include <Util/FTMath.h>
#include <Rendering/Camera/FTCamera.h>
#include <Rendering/FTDirector.h>
#include "Action/FTActionManager.h"


FTNode::FTNode() : perform_frustrum_cull_(false),
                              paused_(false),
                              is_active_(false),
                              rotation_transform_(new FTTransformRotation),
                              position_transform_(new FTTransformPosition()),
                              scale_transform_(new FTTransformScale()),
                              parent_(nullptr),
                              view_(nullptr),
                              scene_(nullptr) {

}

bool FTNode::isVisible(FTCamera* camera) {
    return camera->testNodeVisible(this);
}

void FTNode::visit(FTCamera* camera, std::stack<glm::mat4>& matrix_stack, bool parent_updated) {
    parent_updated |= updateMatrices();
    glm::mat4 model_matrix = matrix_stack.top() * getTransformMatrix();
    if (perform_frustrum_cull_) {
        if (parent_updated)
            updateAAB(model_matrix);
        if (!isVisible(camera))
            return;
    }

    glm::mat4 mvp = camera->getViewProjectionMatrix() * model_matrix;

    this->pre_draw(mvp);
    this->draw();
    this->post_draw();


    matrix_stack.push(model_matrix);
    for (auto it = children_.begin(); it != children_.end(); ++it) {
        (*it)->visit(camera, matrix_stack, parent_updated);
    }
    matrix_stack.pop();
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
    if (is_active_)
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
    if (is_active_)
        child_ptr->onEnter();
}


bool FTNode::updateMatrices() {
    if (!getDirty())
        return false;
    scale_transform_->updateMatrices();
    rotation_transform_->updateMatrices();


    auto rotate_scale_matrix = rotation_transform_->getTransformMatrix() * scale_transform_->getTransformMatrix();
    glm::vec4 offset = glm::vec4(-anchor_point_.x * size_.x, -anchor_point_.y * size_.y, -anchor_point_.z * size_.z, 1);

    auto rotated_scale_offset = rotate_scale_matrix * offset;

    position_transform_->setPosition(glm::vec3(unaltered_position_.x + rotated_scale_offset.x, unaltered_position_.y + rotated_scale_offset.y, unaltered_position_.z + rotated_scale_offset.z));
    position_transform_->updateMatrices();

    transform_matrix = position_transform_->getTransformMatrix() * rotate_scale_matrix;
    transform_dirty_ = false;
    return true;
}

void FTNode::updateAAB(const glm::mat4& model_matrix) {
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

    auto min = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
    auto max = glm::vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

    for (int i = 0; i < 8; i++) {
        auto transformed = model_matrix * positions[i];
        max.x = FTMAX(transformed.x, max.x);
        max.y = FTMAX(transformed.y, max.y);
        max.z = FTMAX(transformed.z, max.z);

        min.x = FTMIN(transformed.x, min.x);
        min.y = FTMIN(transformed.y, min.y);
        min.z = FTMIN(transformed.z, min.z);
    }

    aab_extents_ = (max - min) / 2.0f;
    aab_center_ = (max + min) / 2.0f;
}

void FTNode::runAction(std::unique_ptr<FTAction>&& action) {
    FTEngine::getDirector()->getActionManager()->addAction(this, std::move(action));
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

void FTNode::onEnter() {
    is_active_ = true;
    for (auto it = children_.begin(); it != children_.end(); ++it)
        (*it)->onEnter();
}

void FTNode::onExit() {
    is_active_ = false;
    for (auto it = children_.begin(); it != children_.end(); ++it)
        (*it)->onExit();
}