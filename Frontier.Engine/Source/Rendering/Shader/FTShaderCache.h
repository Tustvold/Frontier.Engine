#pragma once
#include <Frontier.h>
#include <GL/glew.h>

#include <FTDictionary.h>
#include <FTDictionaryUtil.h>
#include "FTShaderProgram.h"

// Caches the GLPrograms allowing their reuse across the application
class FTShaderCache {
	friend class FTEngine;
public:

	static FTShaderCache* getSharedInstance();

	template <typename Type>
	Type* getShaderProgram() {
		return (Type*)shader_store_->get(&(typeid(Type)));
	}

	bool loadShaderProgram(FTShaderProgram* shader_program);

	void unloadAllShaders() {
		shader_store_->clear();
	}

private:
	FTShaderCache();
	~FTShaderCache();

	FTDictionary<const std::type_info*, FTShaderProgram, TypeInfoHasher, TypeInfoComparer>* shader_store_;
};
