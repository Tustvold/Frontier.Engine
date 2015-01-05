#pragma once
#include "FTVertexShaderProgram.h"

class FTVertexColorShaderProgram : public FTVertexShaderProgram {
public:
	FTVertexColorShaderProgram();
	~FTVertexColorShaderProgram();

private:
	static const char* fragment_shader_source_;
	static const char* vertex_shader_source_;
};
