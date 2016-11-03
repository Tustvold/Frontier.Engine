#pragma once
#include "FTVertexTextureShaderProgram.h"

class FTFontShader : public FTVertexTextureShaderProgram {
public:
    FTFontShader();
    ~FTFontShader();

    bool compile() override {
        return createShaderProgram(vertex_shader_source_, fragment_shader_source_);
    }

    GLint getFillColorUniformID() const {
        return fill_color_uniform_id_;
    }

    bool load() override;

protected:
    GLint fill_color_uniform_id_;


    static const char* vertex_shader_source_;
    static const char* fragment_shader_source_;
};
