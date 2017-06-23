#pragma once
#include <Frontier.h>
#include <Rendering/Shader/CircleShaderProgram.h>
#include "Plane.h"

NS_FT_BEGIN

class CircleSprite : public Mesh<VertexTexture<glm::vec2>> {
private:
    typedef Mesh<VertexTexture<glm::vec2>> CircleSpriteBase_;
public:
    explicit CircleSprite(float radius, const glm::vec3& color, CircleShaderProgram* shader = ShaderNode::getShaderUtil<CircleShaderProgram>());
    virtual ~CircleSprite();

    virtual void pre_draw(const Camera* camera) override;
    virtual void post_draw() override;

protected:
};

NS_FT_END