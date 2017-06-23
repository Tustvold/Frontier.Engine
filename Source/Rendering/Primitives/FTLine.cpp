#include "FTLine.h"

NS_FT_BEGIN

FTLine::FTLine(const glm::vec2& p1, const glm::vec2& p2, float thickness, const glm::vec3& color, FTVertexShaderProgramColor* shader):
    FTPlane(glm::vec2(glm::length(p2 - p1), thickness), color, shader) {
    auto delta = p2 - p1;
    auto length = glm::length(delta);
    auto costheta = delta.x / length;

    glm::quat quat;
    quat.x = 0;
    quat.y = 0;
    quat.z = sqrtf((1 - costheta) / 2.0f);
    quat.w = sqrtf((1 + costheta) / 2.0f);

    if (delta.y < 0.0f)
        quat.w *= -1.0f;

    setAnchorPoint(glm::vec2(0, 0.5f));
    setPosition(p1);
    setRotationQuaternion(quat);
}

NS_FT_END