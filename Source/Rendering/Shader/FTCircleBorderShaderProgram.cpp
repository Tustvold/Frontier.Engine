#include "FTCircleBorderShaderProgram.h"
#include "Rendering/FTShaderNode.h"

const char* FTCircleBorderShaderProgram::fragment_shader_source_ = {
    "#version 140\n\
	\n\
	in vec2 UV;\n\
	\n\
	out vec4 color;\n\
	\n\
    uniform vec3 fill_color;\n\
    uniform float border;\n\
	\n\
	void main(){\n\
		\n\
        float dist = length(UV);\n\
        float delta = fwidth(dist);\n\
        float t =   - smoothstep(1.0 - delta, 1.0, dist)\n\
                    + smoothstep(1.0 - border - delta, 1.0 - border, dist);\n\
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
        UV = vertexUV;\n\
        \n\
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

void FTCircleBorderShaderProgram::updateUniforms(const FTCamera *camera, const FTShaderNode *node) {
    FTCircleShaderProgram::updateUniforms(camera, node);

    glUniform1f(border_uniform_id_, node->getMaterial()->border_thickness);
}
