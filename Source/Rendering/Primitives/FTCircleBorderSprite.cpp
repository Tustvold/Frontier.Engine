#include "FTCircleBorderSprite.h"

FTCircleBorderSprite::FTCircleBorderSprite(float radius, const glm::vec3& color, float border, FTCircleBorderShaderProgram* shader) :
    FTCircleSprite(radius, color, shader), 
    border_(border){
}

FTCircleBorderSprite::~FTCircleBorderSprite() {
}

void FTCircleBorderSprite::pre_draw(const glm::mat4& mvp) {
    FTCircleSprite::pre_draw(mvp);
    
    auto& scale = getScale();

    glUniform1f(((FTCircleBorderShaderProgram*)current_shader_program_)->getBorderUniformID(), border_ * FTMIN(scale.x, scale.y));
}