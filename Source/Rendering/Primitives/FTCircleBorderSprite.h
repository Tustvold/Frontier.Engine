#pragma once
#include <Frontier.h>
#include "FTCircleSprite.h"
#include <Rendering/Shader/FTCircleBorderShaderProgram.h>


class FTCircleBorderSprite : public FTCircleSprite {
public:
    explicit FTCircleBorderSprite(float radius, FTCircleBorderShaderProgram* shader = FTShaderNode::getShaderUtil<FTCircleBorderShaderProgram>());
    virtual ~FTCircleBorderSprite();
protected:
};
