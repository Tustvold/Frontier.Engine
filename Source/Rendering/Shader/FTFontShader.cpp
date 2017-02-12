#include "FTFontShader.h"
#include "Rendering/FTShaderNode.h"

const char* FTFontShader::fragment_shader_source_ = {
    "#version 140\n\
    precision highp float;\
	\n\
	in vec2 UV;\n\
	\n\
	uniform sampler2D textureSampler;\n\
    uniform vec3 fill_color;\n\
	out vec4 color;\n\
	\n\
    float contour(in float d, in float w) {\n\
        return smoothstep(0.5 - w, 0.5 + w, d);\n\
    }\n\
    \n\
    float samp(in vec2 uv, float w) {\n\
        return contour(texture2D(textureSampler, uv).r, w);\n\
    }\n\
	void main(){\n\
		float dist = texture2D(textureSampler, UV).r;\n\
        float width = fwidth(dist);\n\
        float alpha = contour(dist, width);\
        float dscale = 0.354;\
        vec2 duv = dscale * (dFdx(UV) + dFdy(UV));\
        vec4 box = vec4(UV-duv, UV+duv);\
        float asum = samp( box.xy, width )\n\
                           + samp( box.zw, width )\n\
                           + samp( box.xw, width )\n\
                           + samp( box.zy, width );\
        alpha = (alpha + 0.5 * asum) / 3.0;\n\
		color = vec4(fill_color,alpha);\n\
		\n\
	}"
};

const char* FTFontShader::vertex_shader_source_ = {
    "#version 140\n\
	#extension GL_ARB_explicit_attrib_location :require \n\
	\n\
	layout(location = 0) in vec3 vertexPosition_modelspace;\n\
	layout(location = 2) in vec2 vertexUV;\n\
	\n\
	uniform mat4 MVP;\n\
	out vec2 UV;\n\
	\n\
	void main(){\n\
		gl_Position = MVP * vec4(vertexPosition_modelspace, 1);\n\
		UV = vertexUV;\n\
	}"
};

FTFontShader::FTFontShader() : fill_color_uniform_id_(-1) {

}

FTFontShader::~FTFontShader() {
}

bool FTFontShader::load() {
    if (!FTVertexTextureShaderProgram::load())
        return false;
    fill_color_uniform_id_ = glGetUniformLocation(program_id_, "fill_color");
    return fill_color_uniform_id_ != -1;
}

void FTFontShader::updateUniforms(const FTCamera *camera, const FTShaderNode *node) {
    FTVertexShaderProgram::updateUniforms(camera, node);

    auto color = node->getMaterial()->diffuse_color;
    glUniform3f(fill_color_uniform_id_, color.x, color.y, color.z);
}
