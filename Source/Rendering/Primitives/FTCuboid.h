#pragma once
#include <Frontier.h>
#include <Rendering/Mesh/FTIndexedMesh.h>
#include <Rendering/Shader/FTVertexColorShaderProgram.h>

NS_FT_BEGIN

class FTCuboid : public FTIndexedMesh<FTVertexColorNormal<glm::vec3>, uint16_t> {
public:
    FTCuboid(const glm::vec3& origin, const glm::vec3& size, const glm::vec3 face_colors[6], FTVertexColorShaderProgram* shader = FTShaderNode::getShaderUtil<FTVertexColorShaderProgram>());

    FTCuboid(const glm::vec3& origin, const glm::vec3& size, const glm::vec3& color, FTVertexColorShaderProgram* shader = FTShaderNode::getShaderUtil<FTVertexColorShaderProgram>());

private:
    void load(const glm::vec3& origin, const glm::vec3& size, const glm::vec3 face_colors[6]);
    typedef FTIndexedMesh<FTVertexColorNormal<glm::vec3>, uint16_t> FTCuboidBase_;
};

NS_FT_END