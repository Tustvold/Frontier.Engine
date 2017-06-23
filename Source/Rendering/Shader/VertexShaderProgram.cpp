#include <Rendering/ShaderNode.h>
#include "VertexShaderProgram.h"

NS_FT_BEGIN

const char* VertexShaderProgram::fragment_shader_source_ = {
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

const char* VertexShaderProgram::vertex_shader_source_ = {
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

VertexShaderProgram::VertexShaderProgram() : mvp_uniform_(-1) {

}

VertexShaderProgram::~VertexShaderProgram() {
}

bool VertexShaderProgram::load() {
    if (!ShaderProgram::load())
        return false;
    mvp_uniform_ = glGetUniformLocation(program_id_, "MVP");
    return mvp_uniform_ != -1;
}

void VertexShaderProgram::updateUniforms(const Camera *camera, ShaderNode *node) {
    glm::mat4 mvp = camera->getViewProjectionMatrix() * node->getModelMatrix();
    glUniformMatrix4fv(mvp_uniform_, 1, GL_FALSE, (const GLfloat *)&mvp);
}

NS_FT_END