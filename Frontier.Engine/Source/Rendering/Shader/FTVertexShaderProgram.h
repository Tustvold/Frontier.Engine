#pragma once
#include "FTShaderProgram.h"


class FTVertexShaderProgram : public FTShaderProgram {
public:

	virtual ~FTVertexShaderProgram();

	virtual bool load() override;

	void updateMvpUniforms(const GLfloat* mvp);

protected:
	FTVertexShaderProgram(const char* vertex_shader, const char* fragment_shader) : FTShaderProgram(vertex_shader,fragment_shader) {
		
	}

private:

	static char* fragment_shader_source_;
	static char* vertex_shader_source_;

	GLuint mvp_uniform_;
};
