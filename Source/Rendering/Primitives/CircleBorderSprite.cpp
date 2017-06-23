#include "CircleBorderSprite.h"

NS_FT_BEGIN

CircleBorderSprite::CircleBorderSprite(float radius, const glm::vec3& color, float border, CircleBorderShaderProgram* shader) :
    CircleSprite(radius, color, shader) {
    material_.border_thickness = border;
}

CircleBorderSprite::~CircleBorderSprite() {
}

NS_FT_END