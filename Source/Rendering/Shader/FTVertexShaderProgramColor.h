#pragma once
#include "FTVertexShaderProgram.h"


class FTVertexShaderProgramColor : public FTVertexShaderProgram {
public:

    FTVertexShaderProgramColor();

    virtual ~FTVertexShaderProgramColor();

    bool load() override;

    bool compile() override {
        return createShaderProgram(vertex_shader_source_, fragment_shader_source_);
    }

    void updateUniforms(const FTCamera *camera, const FTShaderNode *node) override;

private:

    static const char* fragment_shader_source_;
    static const char* vertex_shader_source_;

    GLint fill_color_uniform_id_;
};
