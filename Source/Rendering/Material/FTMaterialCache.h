#pragma once
#include <Frontier.h>
#include "FTMaterial.h"
#include <unordered_map>
#include <typeindex>

NS_FT_BEGIN

// Caches the GLPrograms allowing their reuse across the application
class FTMaterialCache {
    friend class FTDirector;
public:

    FTMaterial* getMaterial(const std::string& name) {
        auto it = store_.find(name);
        if (it == store_.end())
            return nullptr;
        return &it->second;
    }

    FTMaterial* loadMaterial(const std::string& name, const FTMaterial& material) {
        auto it = store_.find(name);
        if (it != store_.end())
            return &it->second; //Already loaded

        store_[name] = material;
        return &store_.find(name)->second;
    }

private:
    FTMaterialCache();
    ~FTMaterialCache();



    std::unordered_map<std::string, FTMaterial> store_;
};

NS_FT_END