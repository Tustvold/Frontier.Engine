#include "CircleSprite.h"
#include <Rendering/View.h>

NS_FT_BEGIN

CircleSprite::CircleSprite(float radius, const glm::vec3& color, CircleShaderProgram* shader) :
    CircleSpriteBase_(shader) {

    auto data = std::make_shared<MeshData<VertexTexture<glm::vec2>>>(4);

    auto vertices = data->getVertices().data();

    VertexTexture<glm::vec2> vertex;
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
    data->setBoundingShape(std::make_unique<BoundingCuboid>(glm::vec3(radiusx2, radiusx2, 0)));

    loadMeshData(data.get(), true);

    material_.diffuse_color = color;
}

CircleSprite::~CircleSprite() {
}

void CircleSprite::pre_draw(const Camera* camera) {
    CircleSpriteBase_::pre_draw(camera);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

void CircleSprite::post_draw() {
    glDisable(GL_BLEND);
}

NS_FT_END