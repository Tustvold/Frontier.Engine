#include "FTVertexShaderProgram.h"

const char* FTVertexShaderProgram::fragment_shader_source_ = {
	"#version 140\n\
	\n\
	out vec3 color;\n\
	\n\
	void main(){\n\
		\n\
		color = vec3(1,0,0);\n\
		\n\
	}"
};

const char* FTVertexShaderProgram::vertex_shader_source_ = {
	"#version 140\n\
	#extension GL_ARB_explicit_attrib_location :require \n\
	\n\
	layout(location = 0) in vec3 vertexPosition_modelspace;\n\
	\n\
	uniform mat4 MVP;\n\
	\n\
	void main(){\n\
		\n\
		gl_Position = MVP * vec4(vertexPosition_modelspace, 1);\n\
		\n\
	}"
};

FTVertexShaderProgram::FTVertexShaderProgram() : FTShaderProgram(vertex_shader_source_, fragment_shader_source_) {

}

FTVertexShaderProgram::~FTVertexShaderProgram() {
}

bool FTVertexShaderProgram::load() {
	mvp_uniform_ = glGetUniformLocation(program_id_, "MVP");
	return mvp_uniform_ != -1;
}

void FTVertexShaderProgram::updateMvpUniforms(const GLfloat* mvp) {
	glUniformMatrix4fv(mvp_uniform_, 1, GL_FALSE, mvp);
}
