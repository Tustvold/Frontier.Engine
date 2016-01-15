#include "FTFontShader.h"

const char* FTFontShader::fragment_shader_source_ = {
    "#version 140\n\
	\n\
	in vec2 UV;\n\
	\n\
	uniform sampler2D textureSampler;\n\
    uniform vec3 fill_color;\n\
	// Ouput data\n\
	out vec4 color;\n\
	\n\
	void main(){\n\
		\n\
		color = vec4(fill_color,texture2D(textureSampler, UV).r);\n\
		\n\
	}"
};

const char* FTFontShader::vertex_shader_source_ = {
    "#version 140\n\
	#extension GL_ARB_explicit_attrib_location :require \n\
	\n\
	layout(location = 0) in vec3 vertexPosition_modelspace;\n\
	layout(location = 2) in vec2 vertexUV;\n\
	\n\
	uniform mat4 MVP;\n\
	out vec2 UV;\n\
	\n\
	void main(){\n\
		gl_Position = MVP * vec4(vertexPosition_modelspace, 1);\n\
		UV = vertexUV;\n\
	}"
};

FTFontShader::FTFontShader() : fill_color_uniform_id_(-1) {

}

FTFontShader::~FTFontShader() {
}

bool FTFontShader::load() {
    if (!FTVertexTextureShaderProgram::load())
        return false;
    fill_color_uniform_id_ = glGetUniformLocation(program_id_, "fill_color");
    return fill_color_uniform_id_ != -1;
}
