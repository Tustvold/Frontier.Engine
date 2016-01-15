#include "FTBoundingCuboid.h"
#include <Rendering/FTNode.h>
#include <Util/FTMath.h>
#include <Rendering/Camera/FTCamera.h>


FTBoundingCuboid::FTBoundingCuboid(const glm::vec3& size) : size_(size) {

}

FTBoundingCuboid::FTBoundingCuboid(const glm::vec3& origin, const glm::vec3& size) : origin_(origin), size_(size) {
}

FTBoundingCuboid::~FTBoundingCuboid() {
}

void FTBoundingCuboid::visit() {
    FTBoundingShape::visit();
    computeWorldAABFromLocalAAB(origin_, size_, aab_center_, aab_half_extents_);
}

bool FTBoundingCuboid::visibleInCamera(FTCamera* camera) {
    return camera->testBoundingBox(aab_center_, aab_half_extents_);
}

glm::vec3 FTBoundingCuboid::computeLocalOffset(const glm::vec3& anchor_point) {
    return origin_ + anchor_point * size_;
}

bool FTBoundingCuboid::containsLocalPosition(const glm::vec3& in_position) {
    auto pos = in_position - origin_;
    return pos.x >= 0 && pos.y >= 0 && pos.z >= 0 && pos.x <= size_.x && pos.y <= size_.y && pos.z <= size_.z;
}
