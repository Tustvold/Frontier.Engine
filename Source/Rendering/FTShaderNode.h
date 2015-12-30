#pragma once
#include <Rendering/FTNode.h>
#include <Rendering/Shader/FTVertexShaderProgram.h>
#include <Rendering/Shader/FTShaderCache.h>
#include <FTEngine.h>
#include <Rendering/FTDirector.h>

// A subclass of FTNode which manages a FTVertexShaderProgram
template <typename ShaderProgram>
class FTShaderNode : public FTNode {
public:

    static_assert(std::is_base_of<FTVertexShaderProgram, ShaderProgram>::value, "FTVertexShaderProgram is not base of ShaderProgram");

    FTShaderNode() :
        current_shader_program_(FTEngine::getDirector()->getShaderCache()->getShaderProgram<ShaderProgram>()) {
    }

    void pre_draw(const glm::mat4& mvp) override {
        current_shader_program_->use();
        current_shader_program_->updateMvpUniforms(&mvp[0][0]);
    }

    void draw() override {

    }

protected:
    std::shared_ptr<ShaderProgram> current_shader_program_;
};
