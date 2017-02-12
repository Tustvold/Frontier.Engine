#pragma once
#include <Frontier.h>
#include <Rendering/Shader/FTVertexTextureShaderProgram.h>
#include <Rendering/Mesh/FTMesh.h>

class FTTexturedPlane : public FTMesh<FTVertexTexture<glm::vec2>> {
private:
    typedef FTMesh<FTVertexTexture<glm::vec2>> FTTexturedPlaneBase_;
public:
    explicit FTTexturedPlane(const glm::vec2& dimensions, FTVertexTextureShaderProgram* shader = FTShaderNode::getShaderUtil<FTVertexTextureShaderProgram>());
    virtual ~FTTexturedPlane();

protected:

};
