#pragma once
#include "FTVertexTextureShaderProgram.h"

class FTCircleShaderProgram : public FTVertexShaderProgram {
public:
    FTCircleShaderProgram();
    virtual ~FTCircleShaderProgram();

    virtual bool load() override;

    virtual bool compile() override {
        return createShaderProgram(vertex_shader_source_, fragment_shader_source_);
    }

    GLuint getFillColorUniformId() const {
        return fill_color_uniform_id_;
    }

    GLuint getCenterUniformId() const {
        return center_uniform_id_;
    }

    GLuint getRadiusUniformID() const {
        return radius_uniform_id_;
    }

protected:
    GLuint fill_color_uniform_id_;
    GLuint center_uniform_id_;
    GLuint radius_uniform_id_;

    static const char* vertex_shader_source_;
    static const char* fragment_shader_source_;
};
