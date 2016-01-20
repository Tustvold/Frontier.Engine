#include "FTCube.h"
#include <Rendering/Shader/FTShaderCache.h>
#include <Rendering/BoundingShape/FTBoundingCuboid.h>

FTCube::FTCube(const glm::vec3 face_colors[6], FTVertexColorShaderProgram* shader)
    : FTCubeBase_(shader) {

    auto data = std::make_shared<FTIndexedMeshData<FTVertexColor<glm::vec3>, uint16_t>>(4 * 6, 36);

    auto vertices = data->getVertices().data();
    auto indices = data->getIndices().data();

    FTVertexColor<glm::vec3> vertex;
    int cur_index = 0;
    int vertex_index = 0;
    int indices_index = 0;

    vertex.color_ = face_colors[0];

    vertex.position_ = glm::vec3(1, 0, 0);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(1, 0, 1);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(1, 1, 0);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(1, 1, 1);
    vertices[vertex_index++] = vertex;

    indices[indices_index++] = (cur_index);
    indices[indices_index++] = (cur_index + 2);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 2);
    indices[indices_index++] = (cur_index + 3);

    cur_index += 4;

    vertex.color_ = face_colors[1];
    vertex.position_ = glm::vec3(0, 0, 0);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(0, 1, 0);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(0, 0, 1);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(0, 1, 1);
    vertices[vertex_index++] = vertex;

    indices[indices_index++] = (cur_index);
    indices[indices_index++] = (cur_index + 2);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 2);
    indices[indices_index++] = (cur_index + 3);


    cur_index += 4;

    vertex.color_ = face_colors[2];
    vertex.position_ = glm::vec3(0, 1, 0);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(1, 1, 0);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(0, 1, 1);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(1, 1, 1);
    vertices[vertex_index++] = vertex;

    indices[indices_index++] = (cur_index);
    indices[indices_index++] = (cur_index + 2);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 2);
    indices[indices_index++] = (cur_index + 3);


    cur_index += 4;

    vertex.color_ = face_colors[3];
    vertex.position_ = glm::vec3(0, 0, 0);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(1, 0, 0);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(0, 0, 1);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(1, 0, 1);
    vertices[vertex_index++] = vertex;

    indices[indices_index++] = (cur_index);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 2);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 3);
    indices[indices_index++] = (cur_index + 2);

    cur_index += 4;

    vertex.color_ = face_colors[4];
    vertex.position_ = glm::vec3(0, 0, 1);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(0, 1, 1);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(1, 0, 1);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(1, 1, 1);
    vertices[vertex_index++] = vertex;

    indices[indices_index++] = (cur_index);
    indices[indices_index++] = (cur_index + 2);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 2);
    indices[indices_index++] = (cur_index + 3);


    cur_index += 4;

    vertex.color_ = face_colors[5];
    vertex.position_ = glm::vec3(0, 0, 0);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(1, 0, 0);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(0, 1, 0);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(1, 1, 0);
    vertices[vertex_index++] = vertex;

    indices[indices_index++] = (cur_index);
    indices[indices_index++] = (cur_index + 2);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 2);
    indices[indices_index++] = (cur_index + 3);

    FTAssert(vertex_index == 4 * 6, "Face Count Error");
    FTAssert(indices_index == 36, "Face Count Error");

    data->setVertexCount(vertex_index);
    data->setIndexCount(indices_index);

    loadIndexedMeshData(data.get(), true);

    setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(1, 1, 1)));
}

FTCube::~FTCube() {

}
