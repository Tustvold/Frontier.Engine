#pragma once
#include <Rendering/FTDrawable.h>
#include <Rendering/Camera/FTCamera.h>
#include <Rendering/Shader/FTShaderCache.h>
#include <Rendering/Scene/Transform/FTTransformUtil.h>
#include <Rendering/Shader/FTVertexShaderProgram.h>
#include <FTEngine.h>
#include <stack>

class FTNodeBase : public FTDrawable, public FTTransform {
public:

    // Override to provide custom frustrum culling code
    virtual bool isVisible(const std::shared_ptr<FTCamera>& camera) {
        return camera->testNodeVisible(this);
    }

    virtual void pre_draw() = 0;
    virtual void post_draw() = 0;
    virtual void visit(const std::shared_ptr<FTCamera>& camera, std::stack<glm::mat4>& matrix_stack) = 0;

    // Iterate over children you wish to draw - this allows usage of non-standard containers for children
    virtual void visitChildren(const std::shared_ptr<FTCamera>& camera, std::stack<glm::mat4>& matrix_stack) {
        
    }

    void setPosition(const glm::vec2& position) {
        setPosition(glm::vec3(position.x, position.y,0));
    }

    void setPosition(const glm::vec3& position) {
        transform_dirty_ = true;
        unaltered_position_ = position;

        position_transform_->setPosition(position - anchor_point_*size_);
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

    virtual void updateMatrices() override {
        if (!getDirty())
            return;
        scale_transform_->updateMatrices();
        rotation_transform_->updateMatrices();
        

        auto rotate_scale_matrix = rotation_transform_->getTransformMatrix() * scale_transform_->getTransformMatrix();
        glm::vec4 offset = glm::vec4(-anchor_point_.x * size_.x, -anchor_point_.y * size_.y, -anchor_point_.z * size_.z, 1);

        auto rotated_scale_offset = rotate_scale_matrix * offset;

        position_transform_->setPosition(glm::vec3(unaltered_position_.x + rotated_scale_offset.x, unaltered_position_.y + rotated_scale_offset.y, unaltered_position_.z + rotated_scale_offset.z));
        position_transform_->updateMatrices();

        transform_matrix = position_transform_->getTransformMatrix() * rotate_scale_matrix;
    }

protected:
    FTNodeBase() : perform_frustrum_cull_(false), rotation_transform_(new FTTransformRotation), position_transform_(new FTTransformPosition()), scale_transform_(new FTTransformScale()) {
        
    }
    
    glm::vec3 size_;
    glm::vec3 anchor_point_;
    glm::vec3 unaltered_position_;
    bool perform_frustrum_cull_;

    std::unique_ptr<FTTransformRotation> rotation_transform_;
    std::unique_ptr<FTTransformPosition> position_transform_;
    std::unique_ptr<FTTransformScale> scale_transform_;
};

// The base class of everything within the scene heirarchy
// Manages a shader program which it populates with the camera data
template <typename ShaderProgram>
class FTNode : public FTNodeBase {
public:
   
    static_assert(std::is_base_of<FTVertexShaderProgram, ShaderProgram>::value, "FTVertexShaderProgram is not base of ShaderProgram");
    explicit FTNode() :
        shader_program_(FTEngine::getShaderCache()->getShaderProgram<ShaderProgram>()) {

    }

    // Override to provide custom transforms, custom frustrum culling, children, etc
    virtual void visit(const std::shared_ptr<FTCamera>& camera, std::stack<glm::mat4>& matrix_stack) override {
        updateMatrices();
        if (perform_frustrum_cull_ && !isVisible(camera))
            return;
        glm::mat4 mvp = matrix_stack.top() * getTransformMatrix();
        shader_program_->use();
        shader_program_->updateMvpUniforms(&mvp[0][0]);

        this->pre_draw();
        this->draw();
        this->post_draw();
        shader_program_->cleanup();

        matrix_stack.push(mvp);
        visitChildren(camera, matrix_stack);
        matrix_stack.pop();
    }

    void draw() override {

    }

    void pre_draw() override {

    }

    void post_draw() override {

    }

protected:
    std::shared_ptr<ShaderProgram> shader_program_;
};
