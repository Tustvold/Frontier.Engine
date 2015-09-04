#pragma once
#include "FTVertexShaderProgram.h"

class FTVertexTextureShaderProgram : public FTVertexShaderProgram {
public:
    FTVertexTextureShaderProgram();
    virtual ~FTVertexTextureShaderProgram();

    virtual bool load() override;

    GLuint getTextureUniformId() {
        return texture_uniform_id_;
    }

protected:
    FTVertexTextureShaderProgram(const char* vertex_shader, const char* fragment_shader) : FTVertexShaderProgram(vertex_shader, fragment_shader) {

    }

    static const char* vertex_shader_source_;
    static const char* fragment_shader_source_;

    GLuint texture_uniform_id_;
};
