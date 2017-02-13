#include "FTCircleBorderSprite.h"

FTCircleBorderSprite::FTCircleBorderSprite(float radius, const glm::vec3& color, float border, FTCircleBorderShaderProgram* shader) :
    FTCircleSprite(radius, color, shader) {
    material_.border_thickness = border;
}

FTCircleBorderSprite::~FTCircleBorderSprite() {
}