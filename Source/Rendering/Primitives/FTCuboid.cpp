#include "FTCuboid.h"
#include <glm/gtx/quaternion.hpp>


FTCuboid::FTCuboid(const glm::vec3& origin, const glm::vec3& size, const glm::vec3 face_colors[6], FTVertexColorShaderProgram* shader) :
    FTCuboidBase_(shader) {
    load(origin, size, face_colors);
}

FTCuboid::FTCuboid(const glm::vec3& origin, const glm::vec3& size, const glm::vec3& color, FTVertexColorShaderProgram* shader) : FTCuboidBase_(shader) {
    glm::vec3 colors[] = { color, color, color, color, color, color };
    load(origin, size, colors);
}

void FTCuboid::load(const glm::vec3& origin, const glm::vec3& size, const glm::vec3 face_colors[6]) {
    auto data = std::make_shared<FTIndexedMeshData<FTVertexColorNormal<glm::vec3>, uint16_t>>(4 * 6, 36);

    auto vertices = data->getVertices().data();
    auto indices = data->getIndices().data();

    FTVertexColorNormal<glm::vec3> vertex;
    int cur_index = 0;
    int vertex_index = 0;
    int indices_index = 0;

    vertex.color_ = face_colors[0];

    vertex.normal_ = glm::vec3(1,0,0);
    vertex.position_ = glm::vec3(origin.x + size.x, origin.y, origin.z);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(origin.x + size.x, origin.y, origin.z + size.z);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(origin.x + size.x, origin.y + size.y, origin.z);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(origin.x + size.x, origin.y + size.y, origin.z + size.z);
    vertices[vertex_index++] = vertex;

    indices[indices_index++] = (cur_index);
    indices[indices_index++] = (cur_index + 2);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 2);
    indices[indices_index++] = (cur_index + 3);

    cur_index += 4;

    vertex.normal_ = glm::vec3(-1,0,0);
    vertex.color_ = face_colors[1];
    vertex.position_ = glm::vec3(origin.x, origin.y, origin.z);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(origin.x, origin.y + size.y, origin.z);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(origin.x, origin.y, origin.z + size.z);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(origin.x, origin.y + size.y, origin.z + size.z);
    vertices[vertex_index++] = vertex;

    indices[indices_index++] = (cur_index);
    indices[indices_index++] = (cur_index + 2);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 2);
    indices[indices_index++] = (cur_index + 3);


    cur_index += 4;

    vertex.normal_ = glm::vec3(0,1,0);
    vertex.color_ = face_colors[2];
    vertex.position_ = glm::vec3(origin.x, origin.y + size.y, origin.z);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(origin.x + size.x, origin.y + size.y, origin.z);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(origin.x, origin.y + size.y, origin.z + size.z);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(origin.x + size.x, origin.y + size.y, origin.z + size.z);
    vertices[vertex_index++] = vertex;

    indices[indices_index++] = (cur_index);
    indices[indices_index++] = (cur_index + 2);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 2);
    indices[indices_index++] = (cur_index + 3);


    cur_index += 4;

    vertex.normal_ = glm::vec3(0,-1,0);
    vertex.color_ = face_colors[3];
    vertex.position_ = glm::vec3(origin.x, origin.y, origin.z);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(origin.x + size.x, origin.y, origin.z);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(origin.x, origin.y, origin.z + size.z);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(origin.x + size.x, origin.y, origin.z + size.z);
    vertices[vertex_index++] = vertex;

    indices[indices_index++] = (cur_index);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 2);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 3);
    indices[indices_index++] = (cur_index + 2);

    cur_index += 4;

    vertex.normal_ = glm::vec3(0,0,1);
    vertex.color_ = face_colors[4];
    vertex.position_ = glm::vec3(origin.x, origin.y, origin.z + size.z);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(origin.x, origin.y + size.y, origin.z + size.z);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(origin.x + size.x, origin.y, origin.z + size.z);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(origin.x + size.x, origin.y + size.y, origin.z + size.z);
    vertices[vertex_index++] = vertex;

    indices[indices_index++] = (cur_index);
    indices[indices_index++] = (cur_index + 2);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 1);
    indices[indices_index++] = (cur_index + 2);
    indices[indices_index++] = (cur_index + 3);


    cur_index += 4;

    vertex.normal_ = glm::vec3(0,0,-1);
    vertex.color_ = face_colors[5];
    vertex.position_ = glm::vec3(origin.x, origin.y, origin.z);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(origin.x + size.x, origin.y, origin.z);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(origin.x, origin.y + size.y, origin.z);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(origin.x + size.x, origin.y + size.y, origin.z);
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

    setBoundingShape(std::make_unique<FTBoundingCuboid>(origin, origin + size));
}
