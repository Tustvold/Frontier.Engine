#pragma once
#include "FTCuboid.h"

NS_FT_BEGIN

class FTCube : public FTCuboid {
public:
    explicit FTCube(const glm::vec3& color, FTVertexColorShaderProgram* shader = FTShaderNode::getShaderUtil<FTVertexColorShaderProgram>());

    explicit FTCube(const glm::vec3 face_colors[6], FTVertexColorShaderProgram* shader = FTShaderNode::getShaderUtil<FTVertexColorShaderProgram>());
    ~FTCube();
};

NS_FT_END