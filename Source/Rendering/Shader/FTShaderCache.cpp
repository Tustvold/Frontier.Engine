#include "FTShaderCache.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

FTShaderCache* FTShaderCache::getSharedInstance() {
    static FTShaderCache* cache = new FTShaderCache();
    return cache;
}

FTShaderCache::FTShaderCache() {
    FTLOG("FTShaderCache Init");

}


FTShaderCache::~FTShaderCache() {
    FTLOG("Shader cache destroyed");

}

bool FTShaderCache::loadShaderProgram(const std::shared_ptr<FTShaderProgram>& shader_program) {
    const std::type_index& type = typeid(*shader_program);
    if (shader_store_.find(type) != shader_store_.end())
        return true; //Already loaded


    if (shader_program->load()) {
        shader_store_[type] = shader_program;
        return true;
    }
    else {
        FTAssert(false, "Failed to load shader program!");
    }

    return false;
}
