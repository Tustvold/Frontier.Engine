#include "BoundingShapeWrapper.h"
#include <Rendering/Node.h>

NS_FT_BEGIN

BoundingShapeWrapper::BoundingShapeWrapper(const std::shared_ptr<Node>& wrapped) : wrapped_(wrapped) {
}

glm::vec3 BoundingShapeWrapper::computeLocalOffset(const glm::vec3& anchor_point) {
    return wrapped_->getBoundingShape()->computeLocalOffset(anchor_point);
}

bool BoundingShapeWrapper::visibleInCamera(Camera* camera) {
    return wrapped_->getBoundingShape()->visibleInCamera(camera);
}

glm::vec3 BoundingShapeWrapper::getLayoutSize() const {
    return wrapped_->getBoundingShape()->getLayoutSize();
}

bool BoundingShapeWrapper::containsLocalPosition(const glm::vec3& position) {
    return wrapped_->getBoundingShape()->containsLocalPosition(position);
}

bool BoundingShapeWrapper::containsMousePosition(const glm::vec2& mouse_pos) {
    return wrapped_->getBoundingShape()->containsMousePosition(mouse_pos);
}

NS_FT_END