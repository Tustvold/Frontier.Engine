#pragma once
#include <Frontier.h>
#include <Rendering/Mesh/IndexedMesh.h>
#include "Plane.h"

NS_FT_BEGIN

class Line : public Plane {
public:
    explicit Line(const glm::vec2& p1, const glm::vec2& p2, float thickness, const glm::vec3& color, VertexShaderProgramColor* shader = ShaderNode::getShaderUtil<VertexShaderProgramColor>());
};

NS_FT_END