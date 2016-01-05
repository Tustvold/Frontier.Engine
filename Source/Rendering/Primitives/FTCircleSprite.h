#pragma once
#include <Frontier.h>
#include <Rendering/Shader/FTCircleShaderProgram.h>
#include "FTPlane.h"

class FTCircleSprite : public FTMesh<FTVertexTexture<glm::vec2>> {
private:
    typedef FTMesh<FTVertexTexture<glm::vec2>> FTCircleSpriteBase_;
public:
    explicit FTCircleSprite(float radius, const glm::vec3& color, FTCircleShaderProgram* shader = FTShaderNode::getShaderUtil<FTCircleShaderProgram>());
    virtual ~FTCircleSprite();

    virtual void pre_draw(const glm::mat4& mvp) override;
    virtual void post_draw() override;

protected:
    glm::vec3 fill_color_;
};
