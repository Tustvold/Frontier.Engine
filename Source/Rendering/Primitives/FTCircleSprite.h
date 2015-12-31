#pragma once
#include <Frontier.h>
#include <Rendering/Mesh/FTIndexedTexturedMesh.h>
#include <Rendering/Shader/FTCircleShaderProgram.h>

class FTCircleSprite : public FTIndexedMesh<FTVertex<glm::vec3>, uint16_t> {
private:
    typedef FTIndexedMesh<FTVertex<glm::vec3>, uint16_t> FTCircleSpriteBase_;
public:
    explicit FTCircleSprite(float radius, const glm::vec3& color, FTCircleShaderProgram* shader = FTShaderNode::getShaderUtil<FTCircleShaderProgram>());
    virtual ~FTCircleSprite();

    virtual void pre_draw(const glm::mat4& mvp) override;
    virtual void post_draw() override;

protected:
    float radius_;
    glm::vec3 color_;
};
