#pragma once
#include <Frontier.h>
#include <Rendering/Shader/FTVertexTextureShaderProgram.h>
#include <Rendering/Mesh/FTIndexedTexturedMesh.h>

class FTTexturedPlane : public FTIndexedTexturedMesh<FTVertexTexture<glm::vec3>, uint16_t> {
private:
    typedef FTIndexedTexturedMesh<FTVertexTexture<glm::vec3>, uint16_t> FTTexturedPlaneBase_;
public:
    explicit FTTexturedPlane(FTVertexTextureShaderProgram* shader = FTShaderNode::getShaderUtil<FTVertexTextureShaderProgram>());
    virtual ~FTTexturedPlane();

protected:

};
