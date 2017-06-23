#include "gmock/gmock.h"
#include <Rendering/Mesh/Mesh.h>

USING_NS_FT

TEST(TestMeshData, TestPreAllocate) {
    MeshData<VertexColor<glm::vec3>> mesh(40);
    EXPECT_EQ(mesh.getVertices().capacity(), (size_t)40);
    EXPECT_EQ(mesh.getVertexCount(), (size_t)0);
}

TEST(TestMeshData, TestDynamic) {
    MeshData<VertexColor<glm::vec3>> mesh(10);
    auto& vertices = mesh.getVertices();

    for (int i = 0; i < 15; i++) {
        vertices.push_back(VertexColor<glm::vec3>(glm::vec3(i, i, i), glm::vec3(0, 0, 0)));
    }
    EXPECT_EQ(mesh.getVertexCount(), (size_t)15);
}

TEST(TestMeshData, TestData) {
    MeshData<VertexColor<glm::vec3>> mesh(10);
    auto vertices = mesh.getVertices().data();
    for (int i = 0; i < 10; i++) {
        vertices[i] = VertexColor<glm::vec3>(glm::vec3(i, i, i), glm::vec3(0, 0, 0));
    }
    EXPECT_EQ(mesh.getVertexCount(), (size_t)0);
    mesh.setVertexCount(10);
    EXPECT_EQ(mesh.getVertexCount(), (size_t)10);

    EXPECT_THROW(mesh.setVertexCount(15), FTException);
}
