#include "VertexTextureShaderProgram.h"
#include "Rendering/ShaderNode.h"

NS_FT_BEGIN

const char* VertexTextureShaderProgram::fragment_shader_source_ = {
    "#version 140\n\
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

const char* VertexTextureShaderProgram::vertex_shader_source_ = {
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

VertexTextureShaderProgram::VertexTextureShaderProgram() : texture_uniform_id_(-1) {
}

VertexTextureShaderProgram::~VertexTextureShaderProgram() {

}

bool VertexTextureShaderProgram::load() {
    if (!VertexShaderProgram::load())
        return false;
    texture_uniform_id_ = glGetUniformLocation(program_id_, "textureSampler");
    return texture_uniform_id_ != -1;
}

void VertexTextureShaderProgram::updateUniforms(const Camera *camera, ShaderNode *node) {
    VertexShaderProgram::updateUniforms(camera, node);
    auto& texture = node->getMaterial()->texture;

    // TODO: Support using multiple texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->getTextureId());
    glUniform1i(texture_uniform_id_, 0);
}

NS_FT_END
