#include "FTCircleSprite.h"
#include <Rendering/FTView.h>

FTCircleSprite::FTCircleSprite(float radius, const glm::vec3& color, FTCircleShaderProgram* shader) :
    FTCircleSpriteBase_(shader),
    radius_(radius), 
    color_(color) {
    auto data = std::make_shared<FTIndexedMeshData<FTVertex<glm::vec3>, uint16_t>>(4 * 6, 36);

    auto vertices = data->getVertices().data();
    auto indices = data->getIndices().data();

    // This helps prevent clipping at the border of the shape
    float epsilon = 1.0f;

    auto radiusx2 = radius + radius;

    FTVertex<glm::vec3> vertex;
    int vertex_index = 0;
    int indices_index = 0;

    
    vertex.position_ = glm::vec3(-epsilon, -epsilon, 0);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(radiusx2+epsilon, -epsilon, 0);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(-epsilon, radiusx2+epsilon, 0);
    vertices[vertex_index++] = vertex;
    vertex.position_ = glm::vec3(radiusx2+epsilon, radiusx2+epsilon, 0);
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

    setSize(glm::vec2(radiusx2));
}

FTCircleSprite::~FTCircleSprite() {
}

void FTCircleSprite::pre_draw(const glm::mat4& mvp) {
    FTCircleSpriteBase_::pre_draw(mvp);
    
    // First convert to clip space
    auto transposed = mvp * glm::vec4(radius_, radius_, 0, 1);
    auto screen_pos = view_->getCamera()->convertClipSpaceToScreenSpace(transposed);

    auto& scale = getScale();

    auto shader = (FTCircleShaderProgram*)current_shader_program_;

    glUniform3f(shader->getFillColorUniformId(), color_.x, color_.y, color_.z);
    glUniform2f(shader->getCenterUniformId(), screen_pos.x, screen_pos.y);
    glUniform1f(shader->getRadiusUniformID(), radius_ * FTMIN(scale.x, scale.y));

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

void FTCircleSprite::post_draw() {
    glDisable(GL_BLEND);
}