#include "FTBoundingShapeWrapper.h"

FTBoundingShapeWrapper::FTBoundingShapeWrapper(const std::shared_ptr<FTBoundingShape>& wrapped) : wrapped_(wrapped) {
}

glm::vec3 FTBoundingShapeWrapper::computeLocalOffset(const glm::vec3& anchor_point) {
    return wrapped_->computeLocalOffset(anchor_point);
}

bool FTBoundingShapeWrapper::visibleInCamera(FTCamera* camera) {
    return wrapped_->visibleInCamera(camera);
}

glm::vec3 FTBoundingShapeWrapper::getLayoutSize() const {
    return wrapped_->getLayoutSize();
}

bool FTBoundingShapeWrapper::containsLocalPosition(const glm::vec3& position) {
    return wrapped_->containsLocalPosition(position);
}

bool FTBoundingShapeWrapper::containsMousePosition(const glm::vec2& mouse_pos) {
    return wrapped_->containsMousePosition(mouse_pos);
}
