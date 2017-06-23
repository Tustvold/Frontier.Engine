#include "FTBoundingShapeWrapper.h"
#include <Rendering/FTNode.h>

NS_FT_BEGIN

FTBoundingShapeWrapper::FTBoundingShapeWrapper(const std::shared_ptr<FTNode>& wrapped) : wrapped_(wrapped) {
}

glm::vec3 FTBoundingShapeWrapper::computeLocalOffset(const glm::vec3& anchor_point) {
    return wrapped_->getBoundingShape()->computeLocalOffset(anchor_point);
}

bool FTBoundingShapeWrapper::visibleInCamera(FTCamera* camera) {
    return wrapped_->getBoundingShape()->visibleInCamera(camera);
}

glm::vec3 FTBoundingShapeWrapper::getLayoutSize() const {
    return wrapped_->getBoundingShape()->getLayoutSize();
}

bool FTBoundingShapeWrapper::containsLocalPosition(const glm::vec3& position) {
    return wrapped_->getBoundingShape()->containsLocalPosition(position);
}

bool FTBoundingShapeWrapper::containsMousePosition(const glm::vec2& mouse_pos) {
    return wrapped_->getBoundingShape()->containsMousePosition(mouse_pos);
}

NS_FT_END