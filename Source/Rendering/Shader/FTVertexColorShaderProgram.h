#pragma once
#include "FTVertexShaderProgram.h"

class FTVertexColorShaderProgram : public FTVertexShaderProgram {
public:
    FTVertexColorShaderProgram();
    ~FTVertexColorShaderProgram();

    virtual bool compile() override {
        return createShaderProgram(vertex_shader_source_, fragment_shader_source_);
    }

private:
    static const char* fragment_shader_source_;
    static const char* vertex_shader_source_;
};
