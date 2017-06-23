#pragma once

#include <Rendering/Camera/Camera.h>
#include "ShaderProgram.h"

NS_FT_BEGIN

class Node;

class VertexShaderProgram : public ShaderProgram {
public:

    VertexShaderProgram();

    virtual ~VertexShaderProgram();

    virtual bool load() override;

    void updateUniforms(const Camera *camera, ShaderNode *node) override;

    virtual bool compile() override {
        return createShaderProgram(vertex_shader_source_, fragment_shader_source_);
    }

private:

    static const char* fragment_shader_source_;
    static const char* vertex_shader_source_;

    GLint mvp_uniform_;
};

NS_FT_END