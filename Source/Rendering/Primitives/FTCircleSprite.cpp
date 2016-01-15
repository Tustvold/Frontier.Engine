#include "FTCircleSprite.h"
#include <Rendering/FTView.h>

FTCircleSprite::FTCircleSprite(float radius, const glm::vec3& color, FTCircleShaderProgram* shader) :
    FTCircleSpriteBase_(shader), fill_color_(color) {

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
    data->setBoundingShape(std::make_shared<FTBoundingCuboid>(glm::vec3(radiusx2, radiusx2, 0)));

    loadMeshData(data.get(), true);
}

FTCircleSprite::~FTCircleSprite() {
}

void FTCircleSprite::pre_draw(const glm::mat4& mvp) {
    FTCircleSpriteBase_::pre_draw(mvp);
    
    auto shader = (FTCircleShaderProgram*)current_shader_program_;
    glUniform3f(shader->getFillColorUniformID(), fill_color_.x, fill_color_.y, fill_color_.z);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

void FTCircleSprite::post_draw() {
    glDisable(GL_BLEND);
}