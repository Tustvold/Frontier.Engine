#pragma once
#include "VertexShaderProgram.h"

NS_FT_BEGIN

class VertexColorShaderProgram : public VertexShaderProgram {
public:
    VertexColorShaderProgram();
    ~VertexColorShaderProgram();

    virtual bool compile() override {
        return createShaderProgram(vertex_shader_source_, fragment_shader_source_);
    }

private:
    static const char* fragment_shader_source_;
    static const char* vertex_shader_source_;
};

NS_FT_END