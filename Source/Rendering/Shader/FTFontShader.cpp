#include "FTFontShader.h"

const char* FTFontShader::fragment_shader_source_ = {
    "#version 140\n\
	\n\
	in vec2 UV;\n\
	in vec3 fragmentColor;\n\
	\n\
	uniform sampler2D textureSampler;\n\
	// Ouput data\n\
	out vec4 color;\n\
	\n\
	void main(){\n\
		\n\
		color = vec4(fragmentColor,texture2D(textureSampler, UV).r);\n\
		\n\
	}"
};

const char* FTFontShader::vertex_shader_source_ = {
    "#version 140\n\
	#extension GL_ARB_explicit_attrib_location :require \n\
	\n\
	layout(location = 0) in vec3 vertexPosition_modelspace;\n\
	layout(location = 1) in vec3 vertexColor;\n\
	layout(location = 2) in vec2 vertexUV;\n\
	\n\
	uniform mat4 MVP;\n\
	out vec2 UV;\n\
	out vec3 fragmentColor;\n\
	\n\
	void main(){\n\
		gl_Position = MVP * vec4(vertexPosition_modelspace, 1);\n\
		fragmentColor = vertexColor;\n\
		UV = vertexUV;\n\
	}"
};

FTFontShader::FTFontShader() : FTVertexTextureShaderProgram(vertex_shader_source_, fragment_shader_source_) {

}

FTFontShader::~FTFontShader() {
}
