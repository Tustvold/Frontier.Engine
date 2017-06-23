#pragma once
#include "FTVertexShaderProgramColor.h"

NS_FT_BEGIN

class FTCircleShaderProgram : public FTVertexShaderProgramColor {
public:

    virtual bool compile() override {
        return createShaderProgram(vertex_shader_source_, fragment_shader_source_);
    }

protected:
    static const char* vertex_shader_source_;
    static const char* fragment_shader_source_;
};

NS_FT_END