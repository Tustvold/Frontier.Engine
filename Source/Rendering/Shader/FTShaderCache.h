#pragma once
#include <Frontier.h>
#include <GL/glew.h>
#include "FTShaderProgram.h"
#include <typeindex>
#include <unordered_map>

// Caches the GLPrograms allowing their reuse across the application
class FTShaderCache {
	friend class FTEngine;
public:

	static FTShaderCache* getSharedInstance();

	template <typename Type>
	std::shared_ptr<Type> getShaderProgram() {
		auto it = shader_store_.find(typeid(Type));
		FTAssert(it != shader_store_.end(), "Shader %s not found", typeid(Type).name());

		return std::static_pointer_cast<Type>(it->second);
	}

	bool loadShaderProgram(const std::shared_ptr<FTShaderProgram>& shader_program);

	void unloadAllShaders() {
		shader_store_.clear();
	}

private:
	FTShaderCache();
	~FTShaderCache();

	std::unordered_map<std::type_index, std::shared_ptr<FTShaderProgram>> shader_store_;
};
