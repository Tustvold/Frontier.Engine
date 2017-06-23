#pragma once
#include "VertexTextureShaderProgram.h"

NS_FT_BEGIN

class FontShader : public VertexTextureShaderProgram {
public:
    FontShader();
    ~FontShader();

    bool compile() override {
        return createShaderProgram(vertex_shader_source_, fragment_shader_source_);
    }

    bool load() override;

    void updateUniforms(const Camera *camera, ShaderNode *node) override;

protected:
    GLint fill_color_uniform_id_;


    static const char* vertex_shader_source_;
    static const char* fragment_shader_source_;
};

NS_FT_END