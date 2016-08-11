#pragma once
#include "FTCuboid.h"

class FTCube : public FTCuboid {
public:
    explicit FTCube(const glm::vec3& color, FTVertexColorShaderProgram* shader = FTShaderNode::getShaderUtil<FTVertexColorShaderProgram>());

    explicit FTCube(const glm::vec3 face_colors[6], FTVertexColorShaderProgram* shader = FTShaderNode::getShaderUtil<FTVertexColorShaderProgram>());
    ~FTCube();
};
