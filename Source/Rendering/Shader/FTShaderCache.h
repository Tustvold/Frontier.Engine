#pragma once
#include <Frontier.h>
#include "FTShaderProgram.h"
#include <unordered_map>
#include <typeindex>

NS_FT_BEGIN

// Caches the GLPrograms allowing their reuse across the application
class FTShaderCache {
    friend class FTDirector;
public:

    template <typename Type>
    Type* getShaderProgram() {
        static_assert(std::is_base_of<FTShaderProgram, Type>::value, "Shader is not a subclass of FTShaderProgram");
        auto it = shader_store_.find(typeid(Type));
        if (it == shader_store_.end()) {
            loadShaderProgram<Type>(std::make_unique<Type>());
            it = shader_store_.find(typeid(Type));
        }
        FTAssert(it != shader_store_.end(), "Shader %s not found", typeid(Type).name());

        return (Type*)it->second.get();
    }

private:
    FTShaderCache();
    ~FTShaderCache();

    template <typename Type>
    bool loadShaderProgram(std::unique_ptr<Type>&& shader_program) {
        const std::type_index& type = typeid(Type);
        if (shader_store_.find(type) != shader_store_.end())
            return true; //Already loaded


        if (shader_program->load()) {
            shader_store_[type] = std::move(shader_program);
            return true;
        }
        FTAssert(false, "Failed to load shader program!");
        return false;
    }

    std::unordered_map<std::type_index, std::unique_ptr<FTShaderProgram>> shader_store_;
};

NS_FT_END