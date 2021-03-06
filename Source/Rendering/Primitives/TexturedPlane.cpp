#include "TexturedPlane.h"

NS_FT_BEGIN

TexturedPlane::TexturedPlane(const glm::vec2& dimensions, VertexTextureShaderProgram* shader) :
    FTTexturedPlaneBase_(shader) {
    auto data = std::make_shared<MeshData<VertexTexture<glm::vec2>>>(4);

    auto& vertices = data->getVertices();

    VertexTexture<glm::vec2> vertex;

    vertex.position_ = glm::vec2(0, 0);
    vertex.uv_ = glm::vec2(0, 1);
    vertices.push_back(vertex);
    vertex.position_ = glm::vec2(dimensions.x, 0);
    vertex.uv_ = glm::vec2(1, 1);
    vertices.push_back(vertex);
    vertex.position_ = glm::vec2(dimensions.x, dimensions.y);
    vertex.uv_ = glm::vec2(1, 0);
    vertices.push_back(vertex);
    vertex.position_ = glm::vec2(0, dimensions.y);
    vertex.uv_ = glm::vec2(0, 0);
    vertices.push_back(vertex);

    data->setPrimitiveType(GL_TRIANGLE_FAN);
    data->setBoundingShape(std::make_unique<BoundingCuboid>(glm::vec3(dimensions, 0)));

    loadMeshData(data.get(), true);
}

TexturedPlane::~TexturedPlane() {
}

NS_FT_END