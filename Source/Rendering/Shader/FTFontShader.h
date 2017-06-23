#pragma once
#include "FTVertexTextureShaderProgram.h"

class FTFontShader : public FTVertexTextureShaderProgram {
public:
    FTFontShader();
    ~FTFontShader();

    bool compile() override {
        return createShaderProgram(vertex_shader_source_, fragment_shader_source_);
    }

    bool load() override;

    void updateUniforms(const FTCamera *camera, FTShaderNode *node) override;

protected:
    GLint fill_color_uniform_id_;


    static const char* vertex_shader_source_;
    static const char* fragment_shader_source_;
};
