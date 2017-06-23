#pragma once
#include "VertexShaderProgram.h"

NS_FT_BEGIN

class VertexTextureShaderProgram : public VertexShaderProgram {
public:
    VertexTextureShaderProgram();
    virtual ~VertexTextureShaderProgram();

    virtual bool load() override;

    virtual bool compile() override {
        return createShaderProgram(vertex_shader_source_, fragment_shader_source_);
    }

    void updateUniforms(const Camera *camera, ShaderNode *node) override;

protected:

    static const char* vertex_shader_source_;
    static const char* fragment_shader_source_;

    GLint texture_uniform_id_;
};

NS_FT_END