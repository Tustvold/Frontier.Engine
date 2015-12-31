#pragma once
#include "FTCircleShaderProgram.h"

class FTCircleBorderShaderProgram : public FTCircleShaderProgram {
public:
    FTCircleBorderShaderProgram();
    virtual ~FTCircleBorderShaderProgram();

    virtual bool load() override;

    virtual bool compile() override {
        return createShaderProgram(vertex_shader_source_, fragment_shader_source_);
    }

    GLuint getBorderUniformID() const {
        return border_uniform_id_;
    }

protected:
    GLuint border_uniform_id_;

    static const char* vertex_shader_source_;
    static const char* fragment_shader_source_;
};
