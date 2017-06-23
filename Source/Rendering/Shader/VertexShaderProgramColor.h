#pragma once
#include "VertexShaderProgram.h"

NS_FT_BEGIN

class VertexShaderProgramColor : public VertexShaderProgram {
public:

    VertexShaderProgramColor();

    virtual ~VertexShaderProgramColor();

    bool load() override;

    bool compile() override {
        return createShaderProgram(vertex_shader_source_, fragment_shader_source_);
    }

    void updateUniforms(const Camera *camera, ShaderNode *node) override;

private:

    static const char* fragment_shader_source_;
    static const char* vertex_shader_source_;

    GLint fill_color_uniform_id_;
};

NS_FT_END