#pragma once
#include <Rendering/Drawable.h>
#include <Rendering/Transform/FTTransformUtil.h>
#include <vector>
#include "Rendering/Action/Action.h"
#include "Rendering/BoundingShape/BoundingShape.h"
#include "Button.h"

NS_FT_BEGIN

class View;
class Scene;
class Camera;

// The draw_order will be this if the node hasn't been drawn
#define NODE_DRAW_ORDER_INVALID std::numeric_limits<uint32_t>::max()

// The base class of all elements in the scene hierarchy
class Node : public Drawable {
public:


    enum Flags {
        TransformDirty = 1,
        AnchorPointDirty = 1 << 1,
        FrustrumCullEnabled = 1 << 2,
        IsActive = 1 << 3,
        ActionsPaused = 1 << 4,
        IsHidden = 1 << 6,
        
        InitialFlags = FrustrumCullEnabled | TransformDirty
    };

    enum Masks {
        DirtyMask = TransformDirty | AnchorPointDirty,
        BoundingShapeDirtyMask = TransformDirty,
    };

    Node();

    virtual ~Node();

    

    // Override to provide custom frustrum culling code
    virtual bool isVisible(Camera* camera);

    virtual void performDraw(Camera* camera, uint32_t& draw_order);

    virtual void pre_draw(const Camera* camera) {
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
    }

    virtual void visit(const glm::mat4& parent_matrix, bool parent_updated);

    void addChild(const std::shared_ptr<Node>& child);

    void addChild(std::shared_ptr<Node>&& child);

    void setPosition(const glm::vec2& position) {
        setPosition(glm::vec3(position.x, position.y, 0));
    }

    void setPosition(const glm::vec3& position) {
        setDirty(TransformDirty);
        position_transform_->setPosition(position);
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
        return position_transform_->getPosition();
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
        anchor_point_ = anchor_point;
        setDirty(AnchorPointDirty);
    }

    const glm::vec3& getAnchorPoint() const {
        return anchor_point_;
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

    void runAction(std::unique_ptr<Action>&& action);

    void resetAllActions();

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
        if (model_matrix_inv_dirty_) {
            model_matrix_inv_ = glm::inverse(model_matrix_);
            normal_matrix_dirty_ = true;
        }
        return model_matrix_inv_;
    }

    const glm::mat3& getNormalMatrix() {
        if (model_matrix_inv_dirty_ || normal_matrix_dirty_) {
            normal_matrix_ = glm::transpose(getModelMatrixInverse());
        }
        return normal_matrix_;
    }

    void removeChild(Node* node);

    void removeFromParent() {
        parent_->removeChild(this);
    }

    Node* getParent() const {
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

    const std::vector<std::shared_ptr<Node>>& getChildren() const {
        return children_;
    }

    const std::unique_ptr<BoundingShape>& getBoundingShape() const {
        return bounding_shape_;
    }

    void setBoundingShape(std::unique_ptr<BoundingShape>&& shape) {
        bounding_shape_ = std::move(shape);
        bounding_shape_->onAddedToNode(this);
    }

    const std::unique_ptr<Button>& getButton() {
        setButtonEnabled(true);
        return button_;
    }

    void setButtonEnabled(bool enabled);

    glm::vec3 convertMouseToLocalCoordinates(const glm::vec2& mouse_coords);

    bool containsMousePosition(const glm::vec2& mouse_coords) const {
        return bounding_shape_->containsMousePosition(mouse_coords);
    }

    int getTag() const {
        return tag_;
    }

    void setTag(int tag) {
        tag_ = tag;
    }

    uint32_t getDrawOrder() const {
        return draw_order_;
    }

    View* getView() const {
        return view_;
    }

protected:
    std::unique_ptr<BoundingShape> bounding_shape_;
    std::unique_ptr<Button> button_;
    glm::vec3 anchor_point_;

    int flags_;
    int tag_;

    std::unique_ptr<TransformRotation> rotation_transform_;
    std::unique_ptr<TransformPosition> position_transform_;
    std::unique_ptr<TransformScale> scale_transform_;

    glm::mat4 transform_matrix_;
    glm::mat4 model_matrix_;
    glm::mat4 model_matrix_inv_;
    bool model_matrix_inv_dirty_;
    glm::mat3 normal_matrix_;
    bool normal_matrix_dirty_;

    std::vector<std::shared_ptr<Node>> children_;

    Node* parent_;
    View* view_;
    Scene* scene_;
    uint32_t draw_order_; // The number node in the draw order - can be used for scene based priority

    // Called after this node is added to the hierarchy of an View
    virtual void onAddedToView(View* view);

    virtual void onAddedToScene(Scene* scene);

    virtual void onRemovedFromView();

    virtual void onRemovedFromScene();

    virtual void onEnter();

    virtual void onExit();
};

NS_FT_END