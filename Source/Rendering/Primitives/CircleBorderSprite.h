#pragma once
#include <Frontier.h>
#include "CircleSprite.h"
#include <Rendering/Shader/CircleBorderShaderProgram.h>

NS_FT_BEGIN

class CircleBorderSprite : public CircleSprite {
public:
    explicit CircleBorderSprite(float radius, const glm::vec3& color, float border, CircleBorderShaderProgram* shader = ShaderNode::getShaderUtil<CircleBorderShaderProgram>());
    virtual ~CircleBorderSprite();
protected:
};

NS_FT_END