#pragma once
#include <Frontier.h>
#include <Rendering/Mesh/FTIndexedMesh.h>
#include "FTPolygon.h"

class FTPolygonBorderSprite : public FTPolygon {
public:
    explicit FTPolygonBorderSprite(const glm::vec3& color, FTVertexShaderProgramColor* shader = FTShaderNode::getShaderUtil<FTVertexShaderProgramColor>());


    void load(std::vector<glm::vec2>&& vertices) override;
};
