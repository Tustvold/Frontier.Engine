#include "FTCircleShaderProgram.h"
const char* FTCircleShaderProgram::fragment_shader_source_ = {
    "#version 140\n\
	\n\
	out vec4 color;\n\
	\n\
    uniform vec3 fill_color;\n\
    uniform vec2 center;\n\
    uniform float radius;\n\
	\n\
	void main(){\n\
		\n\
        float dist = length(gl_FragCoord.xy - center);\n\
        color = vec4(fill_color, 1.0 - smoothstep(radius-1.0, radius+1.0, dist));\n\
		\n\
	}"
};

const char* FTCircleShaderProgram::vertex_shader_source_ = {
    "#version 140\n\
	#extension GL_ARB_explicit_attrib_location :require \n\
	\n\
	layout(location = 0) in vec3 vertexPosition_modelspace;\n\
	\n\
	out vec2 UV;\n\
	\n\
	// Values that stay constant for the whole mesh.\n\
	uniform mat4 MVP;\n\
	\n\
	void main(){\n\
		\n\
		gl_Position = MVP * vec4(vertexPosition_modelspace, 1);\n\
	}"
};

FTCircleShaderProgram::FTCircleShaderProgram() : fill_color_uniform_id_(-1), center_uniform_id_(-1), radius_uniform_id_(-1) {
}

FTCircleShaderProgram::~FTCircleShaderProgram() {

}

bool FTCircleShaderProgram::load() {
    if (!FTVertexShaderProgram::load())
        return false;
    fill_color_uniform_id_ = glGetUniformLocation(program_id_, "fill_color");
    center_uniform_id_ = glGetUniformLocation(program_id_, "center");
    radius_uniform_id_ = glGetUniformLocation(program_id_, "radius");
    return fill_color_uniform_id_ != -1 && center_uniform_id_ != -1 && radius_uniform_id_ != -1;
}
