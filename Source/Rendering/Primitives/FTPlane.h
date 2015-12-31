#pragma once
#include <Frontier.h>
#include <Rendering/Mesh/FTIndexedMesh.h>
#include <Rendering/Shader/FTVertexColorShaderProgram.h>

class FTPlane : public FTIndexedMesh<FTVertexColor<glm::vec3>, uint16_t> {
private:
    typedef FTIndexedMesh<FTVertexColor<glm::vec3>, uint16_t> FTPlaneBase_;
public:
    explicit FTPlane(const glm::vec2& dimensions, const glm::vec3& color, FTVertexColorShaderProgram* shader = FTShaderNode::getShaderUtil<FTVertexColorShaderProgram>());
    virtual ~FTPlane();

protected:

};
