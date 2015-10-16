#pragma once
#include <Frontier.h>
#include "FTShaderProgram.h"
#include <unordered_map>
#include <typeindex>

// Caches the GLPrograms allowing their reuse across the application
class FTShaderCache {
    friend class FTDirector;
public:

    template <typename Type>
    std::shared_ptr<Type> getShaderProgram() {
        static_assert(std::is_base_of<FTShaderProgram, Type>::value, "Shader is not a subclass of FTShaderProgram");
        auto it = shader_store_.find(typeid(Type));
        if (it == shader_store_.end()) {
            loadShaderProgram<Type>(std::make_shared<Type>());
            it = shader_store_.find(typeid(Type));
        }
        FTAssert(it != shader_store_.end(), "Shader %s not found", typeid(Type).name());

        return std::static_pointer_cast<Type>(it->second);
    }

    void unloadAllShaders() {
        shader_store_.clear();
    }

private:
    FTShaderCache();
    ~FTShaderCache();

    template <typename Type>
    bool loadShaderProgram(const std::shared_ptr<Type>& shader_program) {
        const std::type_index& type = typeid(Type);
        if (shader_store_.find(type) != shader_store_.end())
            return true; //Already loaded


        if (shader_program->load()) {
            shader_store_[type] = shader_program;
            return true;
        }
        FTAssert(false, "Failed to load shader program!");
        return false;
    }

    std::unordered_map<std::type_index, std::shared_ptr<FTShaderProgram>> shader_store_;
};
