#pragma once
#include <Rendering/Node.h>
#include <Rendering/Shader/VertexShaderProgram.h>
#include <Rendering/Shader/ShaderCache.h>
#include <Rendering/Material/MaterialCache.h>
#include <Engine.h>
#include <Rendering/Director.h>
#include <Rendering/Material/Material.h>

NS_FT_BEGIN

// A subclass of Node which manages a VertexShaderProgram
class ShaderNode : public Node {
public:
    template <typename ShaderProgram>
    static ShaderProgram* getShaderUtil() {
        return Engine::getDirector()->getShaderCache()->getShaderProgram<ShaderProgram>();
    }

    static Material* getMaterialUtil(const std::string& name) {
        return Engine::getDirector()->getMaterialCache()->getMaterial(name);
    }

    explicit ShaderNode(VertexShaderProgram* shader = getShaderUtil<VertexShaderProgram>()) : current_shader_program_(shader), material_(*getMaterialUtil("Default")) {
    }

    void pre_draw(const Camera* camera) override;

    void draw() override {

    }

    template <typename NewShaderProgram>
    void setShaderProgram() {
        current_shader_program_ = Engine::getDirector()->getShaderCache()->getShaderProgram<NewShaderProgram>();
    }

    bool setMaterial(const std::string& name) {
        auto ret = Engine::getDirector()->getMaterialCache()->getMaterial(name);
        if (ret == nullptr)
            return false;
        material_ = *ret;
        return true;
    }

    void setMaterial(const std::string& name, const Material& material) {
        material_ =  *Engine::getDirector()->getMaterialCache()->loadMaterial(name, material);
    }

    const Material* getMaterial() const {
        return &material_;
    }

protected:
    VertexShaderProgram* current_shader_program_;
    Material material_;
};

NS_FT_END
