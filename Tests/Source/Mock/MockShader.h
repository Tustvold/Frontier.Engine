#pragma once
#include <Rendering/Shader/FTVertexShaderProgram.h>

class MockShader : public FTVertexShaderProgram {

public:
    void updateMvpUniforms(const GLfloat* mvp) override {

    }

    virtual ~MockShader() {

    }

    bool load() override {
        return true;
    }

    bool compile() override {
        return true;
    }
};
