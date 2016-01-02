#include "FTCircleBorderShaderProgram.h"


const char* FTCircleBorderShaderProgram::fragment_shader_source_ = {
    "#version 140\n\
	\n\
	in vec2 UV;\n\
	\n\
	out vec4 color;\n\
	\n\
    uniform vec3 fill_color;\n\
    uniform vec2 center;\n\
    uniform float radius;\n\
    uniform float border;\n\
	\n\
	void main(){\n\
		\n\
        float dist = length(gl_FragCoord.xy - center);\n\
        float delta = fwidth(dist);\n\
        float t =   - smoothstep(radius - delta, radius, dist)\n\
                    + smoothstep(radius - border - delta, radius - border, dist);\n\
        color = vec4(fill_color, t);\n\
		\n\
	}"
};

const char* FTCircleBorderShaderProgram::vertex_shader_source_ = {
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
		\n\
		UV = vertexUV;\n\
	}"
};

FTCircleBorderShaderProgram::FTCircleBorderShaderProgram() : border_uniform_id_(-1) {
}

FTCircleBorderShaderProgram::~FTCircleBorderShaderProgram() {

}

bool FTCircleBorderShaderProgram::load() {
    if (!FTCircleShaderProgram::load())
        return false;
    
    border_uniform_id_ = glGetUniformLocation(program_id_, "border");

    return border_uniform_id_ != -1;
}
