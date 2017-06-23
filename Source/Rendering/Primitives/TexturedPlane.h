#pragma once
#include <Frontier.h>
#include <Rendering/Shader/VertexTextureShaderProgram.h>
#include <Rendering/Mesh/Mesh.h>

NS_FT_BEGIN

class TexturedPlane : public Mesh<VertexTexture<glm::vec2>> {
private:
    typedef Mesh<VertexTexture<glm::vec2>> FTTexturedPlaneBase_;
public:
    explicit TexturedPlane(const glm::vec2& dimensions, VertexTextureShaderProgram* shader = ShaderNode::getShaderUtil<VertexTextureShaderProgram>());
    virtual ~TexturedPlane();

protected:

};

NS_FT_END