#pragma once
#include <Frontier.h>
#include "Polygon.h"

NS_FT_BEGIN

class Plane : public Polygon {
public:
    Plane(const glm::vec2& dimensions, const glm::vec3& color, VertexShaderProgramColor* shader = ShaderNode::getShaderUtil<VertexShaderProgramColor>());
};

NS_FT_END