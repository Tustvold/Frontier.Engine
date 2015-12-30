#pragma once
#include "FTVertexTextureShaderProgram.h"

class FTFontShader : public FTVertexTextureShaderProgram {
public:
    FTFontShader();
    ~FTFontShader();

    virtual bool compile() override {
        return createShaderProgram(vertex_shader_source_, fragment_shader_source_);
    }

protected:
    static const char* vertex_shader_source_;
    static const char* fragment_shader_source_;
};
