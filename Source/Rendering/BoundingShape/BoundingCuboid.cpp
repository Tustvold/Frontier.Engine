#include "BoundingCuboid.h"
#include <Rendering/Node.h>
#include <Util/Math.h>
#include <Rendering/Camera/Camera.h>

NS_FT_BEGIN

BoundingCuboid::BoundingCuboid(const glm::vec3& size) : size_(size) {

}

BoundingCuboid::BoundingCuboid(const glm::vec3& origin, const glm::vec3& size) : origin_(origin), size_(size) {
}

BoundingCuboid::~BoundingCuboid() {
}

void BoundingCuboid::visit() {
    BoundingShape::visit();
    computeWorldAABFromLocalAAB(origin_, size_, aab_center_, aab_half_extents_);
}

bool BoundingCuboid::visibleInCamera(Camera* camera) {
    return camera->testBoundingBox(aab_center_, aab_half_extents_);
}

glm::vec3 BoundingCuboid::computeLocalOffset(const glm::vec3& anchor_point) {
    return origin_ + anchor_point * size_;
}

bool BoundingCuboid::containsLocalPosition(const glm::vec3& in_position) {
    auto pos = in_position - origin_;
    return pos.x >= 0 && pos.y >= 0 && pos.z >= 0 && pos.x <= size_.x && pos.y <= size_.y && pos.z <= size_.z;
}

NS_FT_END