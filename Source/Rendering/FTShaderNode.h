#pragma once
#include <Rendering/FTNode.h>
#include <Rendering/Shader/FTVertexShaderProgram.h>
#include <Rendering/Shader/FTShaderCache.h>
#include <Rendering/Material/FTMaterialCache.h>
#include <FTEngine.h>
#include <Rendering/FTDirector.h>
#include <Rendering/Material/FTMaterial.h>

NS_FT_BEGIN

// A subclass of FTNode which manages a FTVertexShaderProgram
class FTShaderNode : public FTNode {
public:
    template <typename ShaderProgram>
    static ShaderProgram* getShaderUtil() {
        return FTEngine::getDirector()->getShaderCache()->getShaderProgram<ShaderProgram>();
    }

    static FTMaterial* getMaterialUtil(const std::string& name) {
        return FTEngine::getDirector()->getMaterialCache()->getMaterial(name);
    }

    explicit FTShaderNode(FTVertexShaderProgram* shader = getShaderUtil<FTVertexShaderProgram>()) : current_shader_program_(shader), material_(*getMaterialUtil("Default")) {
    }

    void pre_draw(const FTCamera* camera) override;

    void draw() override {

    }

    template <typename NewShaderProgram>
    void setShaderProgram() {
        current_shader_program_ = FTEngine::getDirector()->getShaderCache()->getShaderProgram<NewShaderProgram>();
    }

    bool setMaterial(const std::string& name) {
        auto ret = FTEngine::getDirector()->getMaterialCache()->getMaterial(name);
        if (ret == nullptr)
            return false;
        material_ = *ret;
        return true;
    }

    void setMaterial(const std::string& name, const FTMaterial& material) {
        material_ =  *FTEngine::getDirector()->getMaterialCache()->loadMaterial(name, material);
    }

    const FTMaterial* getMaterial() const {
        return &material_;
    }

protected:
    FTVertexShaderProgram* current_shader_program_;
    FTMaterial material_;
};

NS_FT_END
