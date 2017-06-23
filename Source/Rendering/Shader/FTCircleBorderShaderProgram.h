#pragma once
#include "FTCircleShaderProgram.h"

NS_FT_BEGIN

class FTCircleBorderShaderProgram : public FTCircleShaderProgram {
public:
    FTCircleBorderShaderProgram();
    virtual ~FTCircleBorderShaderProgram();

    virtual bool load() override;

    virtual bool compile() override {
        return createShaderProgram(vertex_shader_source_, fragment_shader_source_);
    }

    void updateUniforms(const FTCamera *camera, FTShaderNode *node) override;

protected:
    GLint border_uniform_id_;

    static const char* vertex_shader_source_;
    static const char* fragment_shader_source_;
};

NS_FT_END