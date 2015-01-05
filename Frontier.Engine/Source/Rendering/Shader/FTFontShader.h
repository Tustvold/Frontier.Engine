#pragma once
#include "FTVertexTextureShaderProgram.h"

class FTFontShader : public FTVertexTextureShaderProgram {
public:
	FTFontShader();
	~FTFontShader();

	virtual void use() override {
		FTVertexTextureShaderProgram::use();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
	}

	virtual void cleanup() override {
		FTVertexTextureShaderProgram::cleanup();
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
	}

protected:
	static const char* vertex_shader_source_;
	static const char* fragment_shader_source_;
};
