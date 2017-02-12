#include "FTVertexShaderProgramColor.h"

const char* FTVertexShaderProgramColor::fragment_shader_source_ = {
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

const char* FTVertexShaderProgramColor::vertex_shader_source_ = {
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

FTVertexShaderProgramColor::FTVertexShaderProgramColor() : fill_color_uniform_id_(-1) {

}

FTVertexShaderProgramColor::~FTVertexShaderProgramColor() {
}

bool FTVertexShaderProgramColor::load() {
    if (!FTVertexShaderProgram::load())
        return false;
    fill_color_uniform_id_ = glGetUniformLocation(program_id_, "fill_color");
    return fill_color_uniform_id_ != -1;
}

void FTVertexShaderProgramColor::updateUniforms(const FTCamera *camera, const FTShaderNode *node) {
    FTVertexShaderProgram::updateUniforms(camera, node);


}
