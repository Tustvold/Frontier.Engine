#pragma once
#include <Frontier.h>
#include <Rendering/Mesh/FTIndexedMesh.h>
#include "FTPlane.h"

NS_FT_BEGIN

class FTLine : public FTPlane {
public:
    explicit FTLine(const glm::vec2& p1, const glm::vec2& p2, float thickness, const glm::vec3& color, FTVertexShaderProgramColor* shader = FTShaderNode::getShaderUtil<FTVertexShaderProgramColor>());
};

NS_FT_END