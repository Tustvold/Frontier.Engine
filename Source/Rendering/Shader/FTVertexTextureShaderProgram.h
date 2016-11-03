#pragma once
#include "FTVertexShaderProgram.h"

class FTVertexTextureShaderProgram : public FTVertexShaderProgram {
public:
    FTVertexTextureShaderProgram();
    virtual ~FTVertexTextureShaderProgram();

    virtual bool load() override;

    GLuint getTextureUniformId() const {
        return texture_uniform_id_;
    }

    virtual bool compile() override {
        return createShaderProgram(vertex_shader_source_, fragment_shader_source_);
    }

protected:

    static const char* vertex_shader_source_;
    static const char* fragment_shader_source_;

    GLint texture_uniform_id_;
};
