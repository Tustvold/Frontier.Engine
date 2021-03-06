#include "VertexShaderProgramColor.h"
#include "Rendering/ShaderNode.h"

NS_FT_BEGIN

const char* VertexShaderProgramColor::fragment_shader_source_ = {
    "#version 140\n\
	\n\
	out vec3 color;\n\
    \n\
    uniform vec3 fill_color;\n\
	\n\
	void main(){\n\
		\n\
		color = fill_color;\n\
		\n\
	}"
};

const char* VertexShaderProgramColor::vertex_shader_source_ = {
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

VertexShaderProgramColor::VertexShaderProgramColor() : fill_color_uniform_id_(-1) {

}

VertexShaderProgramColor::~VertexShaderProgramColor() {
}

bool VertexShaderProgramColor::load() {
    if (!VertexShaderProgram::load())
        return false;
    fill_color_uniform_id_ = glGetUniformLocation(program_id_, "fill_color");
    return fill_color_uniform_id_ != -1;
}

void VertexShaderProgramColor::updateUniforms(const Camera *camera, ShaderNode *node) {
    VertexShaderProgram::updateUniforms(camera, node);

    auto color = node->getMaterial()->diffuse_color;
    glUniform3f(fill_color_uniform_id_, color.x, color.y, color.z);
}

NS_FT_END