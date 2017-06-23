#pragma once

#include <Rendering/Camera/FTCamera.h>
#include "FTShaderProgram.h"

NS_FT_BEGIN

class FTNode;

class FTVertexShaderProgram : public FTShaderProgram {
public:

    FTVertexShaderProgram();

    virtual ~FTVertexShaderProgram();

    virtual bool load() override;

    void updateUniforms(const FTCamera *camera, FTShaderNode *node) override;

    virtual bool compile() override {
        return createShaderProgram(vertex_shader_source_, fragment_shader_source_);
    }

private:

    static const char* fragment_shader_source_;
    static const char* vertex_shader_source_;

    GLint mvp_uniform_;
};

NS_FT_END