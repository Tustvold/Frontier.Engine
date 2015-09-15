#include "gmock/gmock.h"
#include <Rendering/Mesh/FTMesh.h>

TEST(TestMeshData, TestPreAllocate) {
    FTMeshData<FTVertexColor> mesh(40);
    EXPECT_EQ(mesh.getVertices().capacity(), 40);
    EXPECT_EQ(mesh.getVertexCount(), 0);
}

TEST(TestMeshData, TestDynamic) {
    FTMeshData<FTVertexColor> mesh(10);
    auto& vertices = mesh.getVertices();

    for (int i = 0; i < 15; i++) {
        vertices.push_back(FTVertexColor(glm::vec3(i, i, i), glm::vec3(0, 0, 0)));
    }
    EXPECT_EQ(mesh.getVertexCount(), 15);
}

TEST(TestMeshData, TestData) {
    FTMeshData<FTVertexColor> mesh(10);
    auto vertices = mesh.getVertices().data();
    for (int i = 0; i < 10; i++) {
        vertices[i] = FTVertexColor(glm::vec3(i, i, i), glm::vec3(0, 0, 0));
    }
    EXPECT_EQ(mesh.getVertexCount(), 0);
    mesh.setVertexCount(10);
    EXPECT_EQ(mesh.getVertexCount(), 10);

    EXPECT_THROW(mesh.setVertexCount(15), FTException);
}