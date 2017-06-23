#include "VertexColorShaderProgram.h"

NS_FT_BEGIN

const char* VertexColorShaderProgram::fragment_shader_source_ = {
    "#version 140\n\
	\n\
	in vec3 fragmentColor;\n\
	\n\
	// Ouput data\n\
	out vec3 color;\n\
	\n\
	void main(){\n\
		\n\
		color = fragmentColor;\n\
		\n\
	}"
};

const char* VertexColorShaderProgram::vertex_shader_source_ = {
    "#version 140\n\
	#extension GL_ARB_explicit_attrib_location :require \n\
	\n\
	layout(location = 0) in vec3 vertexPosition_modelspace;\n\
	layout(location = 1) in vec3 vertexColor;\n\
	\n\
	out vec3 fragmentColor;\n\
	uniform mat4 MVP;\n\
	\n\
	void main(){\n\
		\n\
		gl_Position = MVP * vec4(vertexPosition_modelspace, 1);\n\
		\n\
		fragmentColor = vertexColor;\n\
	}"
};

VertexColorShaderProgram::VertexColorShaderProgram() {

}


VertexColorShaderProgram::~VertexColorShaderProgram() {
}

NS_FT_END