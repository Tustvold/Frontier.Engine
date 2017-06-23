#include "FTCircleShaderProgram.h"

NS_FT_BEGIN

const char* FTCircleShaderProgram::fragment_shader_source_ = {
    "#version 140\n\
	\n\
	out vec4 color;\n\
   	in vec2 UV;\n\
	\n\
    uniform vec3 fill_color;\n\
	\n\
	void main(){\n\
		\n\
        float dist = length(UV);\n\
        float delta = fwidth(dist);\n\
        color = vec4(fill_color, 1.0 - smoothstep(1.0-delta, 1.0, dist));\n\
		\n\
	}"
};

const char* FTCircleShaderProgram::vertex_shader_source_ = {
    "#version 140\n\
	#extension GL_ARB_explicit_attrib_location :require \n\
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
        UV = vertexUV;\n\
        \n\
	}"
};

NS_FT_END