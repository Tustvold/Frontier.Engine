#pragma once
#include <Rendering/FTDrawable.h>
#include <Rendering/Transform/FTTransformUtil.h>
#include <stack>
#include <vector>
#include "Action/FTAction.h"

class FTView;
class FTScene;
class FTCamera;

// The base class of all elements in the scene hierarchy
class FTNode : public FTDrawable, public FTTransform {
public:

    explicit FTNode();

    // Override to provide custom frustrum culling code
    virtual bool isVisible(FTCamera* camera);

    virtual void pre_draw(const glm::mat4& mvp) {
    }

    virtual void draw() override {
    }

    virtual void post_draw() {
    }

    // Override to provide custom transforms, custom frustrum culling, children, etc
    virtual void visit(FTCamera* camera, std::stack<glm::mat4>& matrix_stack, bool parent_updated);

    void addChild(const std::shared_ptr<FTNode>& child);

    void addChild(std::shared_ptr<FTNode>&& child);

    void setPosition(const glm::vec2& position) {
        setPosition(glm::vec3(position.x, position.y, 0));
    }

    void setPosition(const glm::vec3& position) {
        transform_dirty_ = true;
        unaltered_position_ = position;

        position_transform_->setPosition(position - anchor_point_ * size_);
    }

    void setScale(const glm::vec2& scale) {
        setScale(glm::vec3(scale.x, scale.y, 0));
    }

    void setScale(const glm::vec3& scale) {
        transform_dirty_ = true;
        scale_transform_->setScale(scale);
    }

    void setRotationQuaternion(const glm::quat& quat) {
        transform_dirty_ = true;
        rotation_transform_->setRotationQuaterion(quat);
    }

    const glm::vec3& getPosition() const {
        return unaltered_position_;
    }

    const glm::quat& getRotationQuaternion() const {
        return rotation_transform_->getRotationQuaternion();
    }

    const glm::vec3& getScale() const {
        return scale_transform_->getScale();
    }

    void setSize(const glm::vec2& size) {
        setSize(glm::vec3(size.x, size.y, 0));
    }

    void setSize(const glm::vec3& size) {
        transform_dirty_ = true;
        size_ = size;
    }

    const glm::vec3& getSize() const {
        return size_;
    }

    void setAnchorPoint(const glm::vec2& anchor_point) {
        setAnchorPoint(glm::vec3(anchor_point.x, anchor_point.y, 0));
    }

    void setAnchorPoint(const glm::vec3& anchor_point) {
        transform_dirty_ = true;
        anchor_point_ = anchor_point;
    }

    void setFrustrumCull(bool should_cull) {
        perform_frustrum_cull_ = should_cull;
    }

    virtual bool updateMatrices() override;

    virtual void updateAAB(const glm::mat4& model_matrix);

    const glm::vec3& getAABCenter() const {
        return aab_center_;
    }

    const glm::vec3& getAABHalfExtents() const {
        return aab_extents_;
    }

    bool getActionsPaused() const {
        return paused_;
    }

    // Whether this node is within the hierarchy of the active scene
    bool getIsActive() const {
        return is_active_;
    }

    void runAction(std::unique_ptr<FTAction>&& action);

    void pauseAllActions() {
        paused_ = true;
    }

    void resumeAllActions() {
        paused_ = false;
    }
protected:
    glm::vec3 size_;
    glm::vec3 anchor_point_;
    glm::vec3 unaltered_position_;
    bool perform_frustrum_cull_;
    bool paused_; // Whether the actions on this instance are paused
    bool is_active_; // Whether this instance is connected to a running scene

    glm::vec3 aab_center_;
    glm::vec3 aab_extents_;

    std::unique_ptr<FTTransformRotation> rotation_transform_;
    std::unique_ptr<FTTransformPosition> position_transform_;
    std::unique_ptr<FTTransformScale> scale_transform_;
    std::vector<std::shared_ptr<FTNode>> children_;
    FTNode* parent_;
    FTView* view_;
    FTScene* scene_;

    // Called after this node is added to the hierarchy of an FTView
    virtual void onAddedToView(FTView* view);

    virtual void onAddedToScene(FTScene* scene);

    virtual void onEnter();

    virtual void onExit();
};
