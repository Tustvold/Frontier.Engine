#pragma once
#include <Frontier.h>
#include "Material.h"
#include <unordered_map>
#include <typeindex>

NS_FT_BEGIN

// Caches the GLPrograms allowing their reuse across the application
class MaterialCache {
    friend class Director;
public:

    Material* getMaterial(const std::string& name) {
        auto it = store_.find(name);
        if (it == store_.end())
            return nullptr;
        return &it->second;
    }

    Material* loadMaterial(const std::string& name, const Material& material) {
        auto it = store_.find(name);
        if (it != store_.end())
            return &it->second; //Already loaded

        store_[name] = material;
        return &store_.find(name)->second;
    }

private:
    MaterialCache();
    ~MaterialCache();



    std::unordered_map<std::string, Material> store_;
};

NS_FT_END