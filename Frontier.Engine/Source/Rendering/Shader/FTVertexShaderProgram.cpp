#include "FTVertexShaderProgram.h"

FTVertexShaderProgram::~FTVertexShaderProgram() {
}

bool FTVertexShaderProgram::load() {
	mvp_uniform_ = glGetUniformLocation(program_id_, "MVP");
	return mvp_uniform_ != -1;
}

void FTVertexShaderProgram::updateMvpUniforms(const GLfloat* mvp) {
	glUniformMatrix4fv(mvp_uniform_, 1, GL_FALSE, mvp);
}

