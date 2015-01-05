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
	shader_store_ = new FTDictionary<const std::type_info*, FTShaderProgram, TypeInfoHasher, TypeInfoComparer>();
}


FTShaderCache::~FTShaderCache() {
	FTLOG("Shader cache destroyed");
	shader_store_->release();
}

bool FTShaderCache::loadShaderProgram(FTShaderProgram* shader_program) {
	const std::type_info* type = &(typeid(*shader_program));
	if (shader_store_->contains(type))
		return true; //Already loaded


	if (shader_program->load()) {
		shader_store_->add(type, shader_program);
		return true;
	} else {
		FTAssert(false,"Failed to load shader program!");
	}

	return false;
}
