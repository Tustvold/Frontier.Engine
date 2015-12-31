#include "FTPlane.h"

FTPlane::FTPlane(const glm::vec2& dimensions, const glm::vec3& color, FTVertexColorShaderProgram* shader) :
    FTPlaneBase_(shader) {
    auto data = std::make_shared<FTIndexedMeshData<FTVertexColor<glm::vec3>, uint16_t>>(4 * 6, 36);

    auto vertices = data->getVertices().data();
    auto indices = data->getIndices().data();

    FTVertexColor<glm::vec3> vertex;
    int vertex_index = 0;
    int indices_index = 0;

    vertex.color_ = color;
    vertex.position_ = glm::vec3(0, 0, 0);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(dimensions.x, 0, 0);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(0, dimensions.y, 0);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(dimensions.x, dimensions.y, 0);
    vertices[vertex_index++] = vertex;

    indices[indices_index++] = 0;
    indices[indices_index++] = 2;
    indices[indices_index++] = 1;
    indices[indices_index++] = 1;
    indices[indices_index++] = 2;
    indices[indices_index++] = 3;

    FTAssert(vertex_index == 4, "Face Count Error");
    FTAssert(indices_index == 6, "Face Count Error");

    data->setVertexCount(vertex_index);
    data->setIndexCount(indices_index);

    loadIndexedMeshData(data.get(), true);

    setSize(glm::vec3(dimensions, 0));

}

FTPlane::~FTPlane() {
}
