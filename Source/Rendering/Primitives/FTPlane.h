#pragma once
#include <Frontier.h>
#include "FTPolygon.h"

NS_FT_BEGIN

class FTPlane : public FTPolygon {
public:
    FTPlane(const glm::vec2& dimensions, const glm::vec3& color, FTVertexShaderProgramColor* shader = FTShaderNode::getShaderUtil<FTVertexShaderProgramColor>());
};

NS_FT_END