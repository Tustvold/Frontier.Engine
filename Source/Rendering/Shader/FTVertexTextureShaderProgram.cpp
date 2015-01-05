#include "FTVertexTextureShaderProgram.h"
const char* FTVertexTextureShaderProgram::fragment_shader_source_ = {
	"#version 330 core\n\
	\n\
	in vec2 UV;\n\
	\n\
	out vec3 color;\n\
	\n\
	uniform sampler2D textureSampler;\n\
	\n\
	void main(){\n\
		\n\
		color = texture2D(textureSampler, UV).rgb;\n\
		\n\
	}"
};

const char* FTVertexTextureShaderProgram::vertex_shader_source_ = {
	"#version 330 core\n\
	\n\
	layout(location = 0) in vec3 vertexPosition_modelspace;\n\
	layout(location = 2) in vec2 vertexUV;\n\
	\n\
	out vec2 UV;\n\
	\n\
	// Values that stay constant for the whole mesh.\n\
	uniform mat4 MVP;\n\
	\n\
	void main(){\n\
		\n\
		gl_Position = MVP * vec4(vertexPosition_modelspace, 1);\n\
		\n\
		UV = vertexUV;\n\
	}"
};

FTVertexTextureShaderProgram::FTVertexTextureShaderProgram() : FTVertexShaderProgram(vertex_shader_source_,fragment_shader_source_){
}

FTVertexTextureShaderProgram::~FTVertexTextureShaderProgram() {

}

bool FTVertexTextureShaderProgram::load() {
	if (!FTVertexShaderProgram::load())
		return false;
	texture_uniform_id_ = glGetUniformLocation(program_id_, "textureSampler");
	return texture_uniform_id_ != -1;
}