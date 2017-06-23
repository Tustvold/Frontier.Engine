#include "FTCircleSprite.h"
#include <Rendering/FTView.h>

NS_FT_BEGIN

FTCircleSprite::FTCircleSprite(float radius, const glm::vec3& color, FTCircleShaderProgram* shader) :
    FTCircleSpriteBase_(shader) {

    auto data = std::make_shared<FTMeshData<FTVertexTexture<glm::vec2>>>(4);

    auto vertices = data->getVertices().data();

    FTVertexTexture<glm::vec2> vertex;
    int vertex_index = 0;

    auto radiusx2 = radius * 2.0f;

    vertex.position_ = glm::vec2(0, 0);
    vertex.uv_ = glm::vec2(-1, 1);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec2(radiusx2, 0);
    vertex.uv_ = glm::vec2(1, 1);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec2(radiusx2, radiusx2);
    vertex.uv_ = glm::vec2(1, -1);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec2(0, radiusx2);
    vertex.uv_ = glm::vec2(-1, -1);
    vertices[vertex_index++] = vertex;
    

    FTAssert(vertex_index == 4, "Face Count Error");

    data->setVertexCount(vertex_index);
    data->setPrimitiveType(GL_TRIANGLE_FAN);
    data->setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(radiusx2, radiusx2, 0)));

    loadMeshData(data.get(), true);

    material_.diffuse_color = color;
}

FTCircleSprite::~FTCircleSprite() {
}

void FTCircleSprite::pre_draw(const FTCamera* camera) {
    FTCircleSpriteBase_::pre_draw(camera);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

void FTCircleSprite::post_draw() {
    glDisable(GL_BLEND);
}

NS_FT_END