#pragma once
#include <Frontier.h>
#include <Rendering/Shader/FTVertexTextureShaderProgram.h>
#include <Rendering/Mesh/FTTexturedMesh.h>

class FTTexturedPlane : public FTTexturedMesh<FTVertexTexture<glm::vec2>, uint16_t> {
private:
    typedef FTTexturedMesh<FTVertexTexture<glm::vec2>, uint16_t> FTTexturedPlaneBase_;
public:
    explicit FTTexturedPlane(const glm::vec2& dimensions, FTVertexTextureShaderProgram* shader = FTShaderNode::getShaderUtil<FTVertexTextureShaderProgram>());
    virtual ~FTTexturedPlane();

protected:

};
