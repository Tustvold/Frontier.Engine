#pragma once
#include "FTVertexShaderProgram.h"

class FTVertexTextureShaderProgram : public FTVertexShaderProgram {
public:
    FTVertexTextureShaderProgram();
    virtual ~FTVertexTextureShaderProgram();

    virtual bool load() override;

    virtual bool compile() override {
        return createShaderProgram(vertex_shader_source_, fragment_shader_source_);
    }

    void updateUniforms(const FTCamera *camera, FTShaderNode *node) override;

protected:

    static const char* vertex_shader_source_;
    static const char* fragment_shader_source_;

    GLint texture_uniform_id_;
};
