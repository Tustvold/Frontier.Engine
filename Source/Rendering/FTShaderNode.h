#pragma once
#include <Rendering/FTNode.h>
#include <Rendering/Shader/FTVertexShaderProgram.h>
#include <Rendering/Shader/FTShaderCache.h>
#include <FTEngine.h>
#include <Rendering/FTDirector.h>

// A subclass of FTNode which manages a FTVertexShaderProgram
class FTShaderNode : public FTNode {
public:
    template <typename ShaderProgram>
    static ShaderProgram* getShaderUtil() {
        return FTEngine::getDirector()->getShaderCache()->getShaderProgram<ShaderProgram>();
    }

    explicit FTShaderNode(FTVertexShaderProgram* shader = getShaderUtil<FTVertexShaderProgram>()) : current_shader_program_(shader) {
    }

    void pre_draw(const glm::mat4& mvp) override {
        current_shader_program_->use();
        current_shader_program_->updateMvpUniforms(&mvp[0][0]);
    }

    void draw() override {

    }

    template <typename NewShaderProgram>
    void setShaderProgram() {
        current_shader_program_ = FTEngine::getDirector()->getShaderCache()->getShaderProgram<NewShaderProgram>();
    }

    

protected:
    FTVertexShaderProgram* current_shader_program_;
};
