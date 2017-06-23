#include "BoundingEllipsoid.h"
#include <Rendering/Camera/Camera.h>

NS_FT_BEGIN

BoundingEllipsoid::BoundingEllipsoid(const glm::vec3& radii) : radii_(radii) {
    FTAssert(radii_.x >= 0.0f && radii_.y >= 0.0f && radii_.z >= 0.0f, "Invalid Radii");
}

void BoundingEllipsoid::visit() {
    BoundingShape::visit();
    computeWorldAABFromLocalAAB(glm::vec3(), radii_*2.0f, aab_center_, aab_half_extents_);
}

bool BoundingEllipsoid::containsLocalPosition(const glm::vec3& position) {
    auto adjusted = position - radii_;
    float total = 0.0f;
    if (radii_.x != 0.0f)
        total += adjusted.x / radii_.x * adjusted.x / radii_.x;
    else if (position.x != 0.0f)
        return false;

    if (radii_.y != 0.0f)
        total += adjusted.y / radii_.y * adjusted.y / radii_.y;
    else if (position.y != 0.0f)
        return false;

    if (radii_.z != 0.0f)
        total += adjusted.z / radii_.z * adjusted.z / radii_.z;
    else if (position.z != 0.0f)
        return false;

    return total <= 1.0f;
}

bool BoundingEllipsoid::visibleInCamera(Camera* camera) {
    return camera->testBoundingBox(aab_center_, aab_half_extents_);
}

glm::vec3 BoundingEllipsoid::getLayoutSize() const {
    return radii_ * 2.0f;
}

glm::vec3 BoundingEllipsoid::computeLocalOffset(const glm::vec3& anchor_point) {
    return getLayoutSize() * anchor_point;
}

NS_FT_END