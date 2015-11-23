#pragma once
#include <Frontier.h>
#include <Rendering/Mesh/FTIndexedMesh.h>
#include <Rendering/Shader/FTVertexColorShaderProgram.h>

class FTPlane : public FTIndexedMesh<FTVertexColorShaderProgram, FTVertexColor<glm::vec3>, uint16_t> {
public:
    explicit FTPlane(const glm::vec3& color);
    virtual ~FTPlane();

protected:

};
