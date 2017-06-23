#include "gmock/gmock.h"
#include <Rendering/Mesh/FTIndexedMesh.h>

USING_NS_FT

TEST(TestIndexedMeshData, TestPreAllocate) {
    FTIndexedMeshData<FTVertexColor<glm::vec3>, uint16_t> mesh(40, 80);
    EXPECT_EQ(mesh.getVertices().capacity(), (size_t)40);
    EXPECT_EQ(mesh.getIndices().capacity(), (size_t)80);
    EXPECT_EQ(mesh.getVertexCount(), (size_t)0);
    EXPECT_EQ(mesh.getIndexCount(), (size_t)0);
}

TEST(TestIndexedMeshData, TestDynamic) {
    FTIndexedMeshData<FTVertexColor<glm::vec3>, uint16_t> mesh(10, 10);
    auto& vertices = mesh.getVertices();
    auto& indices = mesh.getIndices();

    for (int i = 0; i < 15; i++) {
        vertices.push_back(FTVertexColor<glm::vec3>(glm::vec3(i, i, i), glm::vec3(0, 0, 0)));
    }

    for (int i = 0; i < 15; i++) {
        indices.push_back(i);
    }
    EXPECT_EQ(mesh.getVertexCount(), (size_t)15);
    EXPECT_EQ(mesh.getIndexCount(), (size_t)15);
}

TEST(TestIndexedMeshData, TestData) {
    FTIndexedMeshData<FTVertexColor<glm::vec3>, uint16_t> mesh(10, 15);
    auto vertices = mesh.getVertices().data();
    auto indices = mesh.getIndices().data();
    for (int i = 0; i < 10; i++) {
        vertices[i] = FTVertexColor<glm::vec3>(glm::vec3(i, i, i), glm::vec3(0, 0, 0));
    }
    for (int i = 0; i < 15; i++) {
        indices[i] = i;
    }

    EXPECT_EQ(mesh.getVertexCount(), (size_t)0);
    EXPECT_EQ(mesh.getIndexCount(), (size_t)0);
    mesh.setVertexCount(10);
    mesh.setIndexCount(15);
    EXPECT_EQ(mesh.getVertexCount(), (size_t)10);
    EXPECT_EQ(mesh.getIndexCount(), (size_t)15);

    EXPECT_THROW(mesh.setVertexCount(15), FTException);
    EXPECT_THROW(mesh.setIndexCount(20), FTException);
}
