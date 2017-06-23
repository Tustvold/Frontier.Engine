#pragma once
#include <Frontier.h>
#include <Rendering/Mesh/IndexedMesh.h>
#include <Rendering/Shader/VertexColorShaderProgram.h>

NS_FT_BEGIN

class Cuboid : public IndexedMesh<VertexColorNormal<glm::vec3>, uint16_t> {
public:
    Cuboid(const glm::vec3& origin, const glm::vec3& size, const glm::vec3 face_colors[6], VertexColorShaderProgram* shader = ShaderNode::getShaderUtil<VertexColorShaderProgram>());

    Cuboid(const glm::vec3& origin, const glm::vec3& size, const glm::vec3& color, VertexColorShaderProgram* shader = ShaderNode::getShaderUtil<VertexColorShaderProgram>());

private:
    void load(const glm::vec3& origin, const glm::vec3& size, const glm::vec3 face_colors[6]);
    typedef IndexedMesh<VertexColorNormal<glm::vec3>, uint16_t> FTCuboidBase_;
};

NS_FT_END