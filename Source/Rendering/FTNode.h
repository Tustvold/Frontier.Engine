#pragma once
#include <Rendering/FTDrawable.h>
#include <Rendering/Transform/FTTransformUtil.h>
#include <stack>
#include <vector>
#include "Action/FTAction.h"
#include <Event/Input/FTMouseDelegate.h>
#include "BoundingShape/FTBoundingShape.h"

class FTView;
class FTScene;
class FTCamera;

// The base class of all elements in the scene hierarchy
class FTNode : public FTDrawable, public FTMouseDelegate {
public:


    enum Flags {
        TransformDirty = 1,
        ChildNodeDirty = 1 << 1,
        FrustrumCullEnabled = 1 << 2,
        IsActive = 1 << 3,
        ActionsPaused = 1 << 4,
        MouseInputEnabled = 1 << 5,
        IsHidden = 1 << 6,
        
        InitialFlags = FrustrumCullEnabled | TransformDirty | ChildNodeDirty
    };

    enum Masks {
        DirtyMask = TransformDirty | ChildNodeDirty,
        BoundingShapeDirtyMask = TransformDirty | ChildNodeDirty,
    };

    FTNode();

    virtual ~FTNode();

    bool onMouseDown(const FTMouseButtonPressedEvent& event) override {
        return false;
    }

    void onMouseDrag(const FTMouseMoveEvent&, int mouse_button) override {

    }

    void onMouseRelease(const FTMouseButtonReleasedEvent& event) override {

    }

    bool onMouseMove(const FTMouseMoveEvent& event) override {
        return false;
    }

    void setMouseInputEnabled(bool enabled);

    bool getMouseDelegateEnabled() const override {
        return (flags_ & IsActive) != 0;
    }

    // Override to provide custom frustrum culling code
    virtual bool isVisible(FTCamera* camera);

    virtual void performDraw(FTCamera* camera);

    virtual void pre_draw(const glm::mat4& mvp) {
    }

    void draw() override {
    }

    virtual void post_draw() {
    }

    void setDirty(Flags dirty_raw) {
        int dirty = dirty_raw & DirtyMask;
        if ((flags_ & dirty) == dirty)
            return;
        flags_ |= dirty;
        if (parent_)
            parent_->setDirty(ChildNodeDirty);
    }

    virtual void visit(const glm::mat4& parent_matrix, bool parent_updated);

    void addChild(const std::shared_ptr<FTNode>& child);

    void addChild(std::shared_ptr<FTNode>&& child);

    void setPosition(const glm::vec2& position) {
        setPosition(glm::vec3(position.x, position.y, 0));
    }

    void setPosition(const glm::vec3& position) {
        setDirty(TransformDirty);
        unaltered_position_ = position;
    }

    void setScale(const glm::vec2& scale) {
        setScale(glm::vec3(scale.x, scale.y, 1));
    }

    void setScale(const glm::vec3& scale) {
        setDirty(TransformDirty);
        scale_transform_->setScale(scale);
    }

    void setRotationQuaternion(const glm::quat& quat) {
        setDirty(TransformDirty);
        rotation_transform_->setRotationQuaterion(quat);
    }

    const glm::vec3& getPosition() const {
        return unaltered_position_;
    }

    const glm::quat& getRotationQuaternion() const {
        return rotation_transform_->getRotationQuaternion();
    }

    virtual const glm::vec3& getScale() const {
        return scale_transform_->getScale();
    }

    void setAnchorPoint(const glm::vec2& anchor_point) {
        setAnchorPoint(glm::vec3(anchor_point.x, anchor_point.y, 0));
    }

    void setAnchorPoint(const glm::vec3& anchor_point) {
        setDirty(TransformDirty);
        anchor_point_ = anchor_point;
    }

    void setFrustrumCull(bool should_cull) {
        if (should_cull)
            flags_ |= FrustrumCullEnabled;
        else
            flags_ &= ~FrustrumCullEnabled;
    }

    virtual bool updateTransformMatrices(const glm::mat4& parent_matrix);

    bool getActionsPaused() const {
        return (flags_ & ActionsPaused) != 0;
    }

    // Whether this node is within the hierarchy of the active scene
    bool getIsActive() const {
        return (flags_ & IsActive) != 0;
    }

    void runAction(std::unique_ptr<FTAction>&& action);

    void pauseAllActions() {
        flags_ |= ActionsPaused;
    }

    void resumeAllActions() {
        flags_ &= ~ActionsPaused;
    }

    const glm::mat4& getTransformMatrix() const {
        return transform_matrix_;
    }

    const glm::mat4& getModelMatrix() const {
        return model_matrix_;
    }

    const glm::mat4& getModelMatrixInverse() {
        if (model_matrix_inv_dirty_)
            model_matrix_inv_ = glm::inverse(model_matrix_);
        return model_matrix_inv_;
    }

    void removeChild(FTNode* node);

    void removeFromParent() {
        parent_->removeChild(this);
    }

    FTNode* getParent() const {
        return parent_;
    }

    bool getHidden() const {
        return (flags_ & IsHidden) != 0;
    }

    void setHidden(bool hidden) {
        if (hidden)
            flags_ |= IsHidden;
        else
            flags_ &= ~IsHidden;
    }

    const std::vector<std::shared_ptr<FTNode>>& getChildren() const {
        return children_;
    }

    const std::shared_ptr<FTBoundingShape>& getBoundingShape() const {
        return bounding_shape_;
    }

    void setBoundingShape(const std::shared_ptr<FTBoundingShape>& shape) {
        bounding_shape_ = shape;
        bounding_shape_->onAddedToNode(this);
    }

    void setBoundingShape(std::shared_ptr<FTBoundingShape>&& shape) {
        bounding_shape_ = std::move(shape);
        bounding_shape_->onAddedToNode(this);
    }

    glm::vec3 convertMouseToLocalCoordinates(const glm::vec2& mouse_coords);

    bool containsMousePosition(const glm::vec2& mouse_coords) {
        return bounding_shape_->containsMousePosition(mouse_coords);
    }

protected:
    std::shared_ptr<FTBoundingShape> bounding_shape_;
    glm::vec3 anchor_point_;

    glm::vec3 unaltered_position_;

    int flags_;

    std::unique_ptr<FTTransformRotation> rotation_transform_;
    std::unique_ptr<FTTransformPosition> position_transform_;
    std::unique_ptr<FTTransformScale> scale_transform_;

    glm::mat4 transform_matrix_;
    glm::mat4 model_matrix_;
    glm::mat4 model_matrix_inv_;
    bool model_matrix_inv_dirty_;

    std::vector<std::shared_ptr<FTNode>> children_;

    FTNode* parent_;
    FTView* view_;
    FTScene* scene_;

    // Called after this node is added to the hierarchy of an FTView
    virtual void onAddedToView(FTView* view);

    virtual void onAddedToScene(FTScene* scene);

    virtual void onRemovedFromView();

    virtual void onRemovedFromScene();

    virtual void onEnter();

    virtual void onExit();
};
