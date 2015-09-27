#pragma once
#include <Rendering/Mesh/FTIndexedMesh.h>
#include <Rendering/Scene/Transform/FTTransformUtil.h>
#include <Rendering/Shader/FTVertexColorShaderProgram.h>

class FTCube : public FTIndexedMesh<FTVertexColorShaderProgram, FTVertexColor<glm::vec3>, uint16_t> {
public:
    explicit FTCube(const glm::vec3 face_colors[6]);
    ~FTCube();

protected:

};
