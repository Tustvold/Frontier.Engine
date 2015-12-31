#pragma once
#include <Rendering/Mesh/FTIndexedMesh.h>
#include <Rendering/Shader/FTVertexColorShaderProgram.h>
#include <Rendering/Mesh/FTVertex.h>

class FTCube : public FTIndexedMesh<FTVertexColor<glm::vec3>, uint16_t> {
private:
    typedef FTIndexedMesh<FTVertexColor<glm::vec3>, uint16_t> FTCubeBase_;
public:
    explicit FTCube(const glm::vec3 face_colors[6], FTVertexColorShaderProgram* shader = FTShaderNode::getShaderUtil<FTVertexColorShaderProgram>());
    ~FTCube();

protected:

};
