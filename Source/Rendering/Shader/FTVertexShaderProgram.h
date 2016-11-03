#pragma once
#include "FTShaderProgram.h"


class FTVertexShaderProgram : public FTShaderProgram {
public:

    FTVertexShaderProgram();

    virtual ~FTVertexShaderProgram();

    virtual bool load() override;

    virtual void updateMvpUniforms(const GLfloat* mvp);

    virtual bool compile() override {
        return createShaderProgram(vertex_shader_source_, fragment_shader_source_);
    }

private:

    static const char* fragment_shader_source_;
    static const char* vertex_shader_source_;

    GLint mvp_uniform_;
};
