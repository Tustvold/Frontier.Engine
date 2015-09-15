#pragma once
#include <Rendering/FTDrawable.h>
#include <Rendering/Camera/FTCamera.h>
#include <Rendering/Shader/FTVertexShaderProgram.h>
#include <Rendering/Shader/FTShaderCache.h>
#include <FTEngine.h>

class IFTNode : public FTDrawable {
public:

    virtual void pre_draw() = 0;
    virtual void post_draw() = 0;
    virtual void visit(const std::shared_ptr<FTCamera>& camera) = 0;

};

// The base class of everything within the scene heirarchy
// Manages a shader program which it populates with the camera data
template <typename Transform, typename ShaderProgram>
class FTNode : public IFTNode {
public:

    explicit FTNode() :
        transform_(new Transform()),
        shader_program_(FTEngine::getShaderCache()->getShaderProgram<ShaderProgram>()) {

    }


    // Override to provide custom transforms, frustrum culling, children, etc
    virtual void visit(const std::shared_ptr<FTCamera>& camera) override {
        transform_->updateMatrices();
        glm::mat4 mvp = camera->getViewProjectionMatrix() * transform_->getTransformMatrix();
        shader_program_->use();
        shader_program_->updateMvpUniforms(&mvp[0][0]);
        this->pre_draw();
        this->draw();
        this->post_draw();
        shader_program_->cleanup();
    }

protected:
    std::unique_ptr<Transform> transform_;
    std::shared_ptr<ShaderProgram> shader_program_;
};
