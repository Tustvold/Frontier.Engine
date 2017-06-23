#pragma once
#include <Frontier.h>
#include "FTCircleSprite.h"
#include <Rendering/Shader/FTCircleBorderShaderProgram.h>

NS_FT_BEGIN

class FTCircleBorderSprite : public FTCircleSprite {
public:
    explicit FTCircleBorderSprite(float radius, const glm::vec3& color, float border, FTCircleBorderShaderProgram* shader = FTShaderNode::getShaderUtil<FTCircleBorderShaderProgram>());
    virtual ~FTCircleBorderSprite();
protected:
};

NS_FT_END