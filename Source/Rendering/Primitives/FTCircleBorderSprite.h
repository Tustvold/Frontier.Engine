#pragma once
#include <Frontier.h>
#include "FTCircleSprite.h"
#include <Rendering/Shader/FTCircleBorderShaderProgram.h>


class FTCircleBorderSprite : public FTCircleSprite {
public:
    explicit FTCircleBorderSprite(float radius, const glm::vec3& color, float border, FTCircleBorderShaderProgram* shader = FTShaderNode::getShaderUtil<FTCircleBorderShaderProgram>());
    virtual ~FTCircleBorderSprite();

    virtual void pre_draw(const glm::mat4& mvp) override;

protected:
    float border_;
};
