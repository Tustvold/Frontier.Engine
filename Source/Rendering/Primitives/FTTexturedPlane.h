#pragma once
#include <Frontier.h>
#include <Rendering/Shader/FTVertexTextureShaderProgram.h>
#include <Rendering/Mesh/FTIndexedTexturedMesh.h>

class FTTexturedPlane : public FTIndexedTexturedMesh<FTVertexTextureShaderProgram, FTVertexTexture<glm::vec3>, uint16_t> {
public:
    explicit FTTexturedPlane();
    virtual ~FTTexturedPlane();

protected:

};
