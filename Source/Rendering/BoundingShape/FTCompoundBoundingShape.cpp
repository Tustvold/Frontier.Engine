#include "FTCompoundBoundingShape.h"

NS_FT_BEGIN

FTCompoundBoundingShape::FTCompoundBoundingShape() {
}

FTCompoundBoundingShape::FTCompoundBoundingShape(const std::vector<std::shared_ptr<FTBoundingShape>>& shapes) : bounding_shapes_(shapes) {

}

FTCompoundBoundingShape::FTCompoundBoundingShape(std::vector<std::shared_ptr<FTBoundingShape>>&& shapes) : bounding_shapes_(std::move(shapes)) {

}

void FTCompoundBoundingShape::onAddedToNode(FTNode* node) {
    for (auto it = bounding_shapes_.begin(); it != bounding_shapes_.end(); ++it) {
        (*it)->onAddedToNode(node);
    }
}

void FTCompoundBoundingShape::visit() {
    for (auto it = bounding_shapes_.begin(); it != bounding_shapes_.end(); ++it) {
        (*it)->visit();
    }
}

bool FTCompoundBoundingShape::containsMousePosition(const glm::vec2& mouse_pos) {
    for (auto it = bounding_shapes_.begin(); it != bounding_shapes_.end(); ++it) {
        if ((*it)->containsMousePosition(mouse_pos))
            return true;
    }
    return false;
}

bool FTCompoundBoundingShape::containsLocalPosition(const glm::vec3& position) {
    for (auto it = bounding_shapes_.begin(); it != bounding_shapes_.end(); ++it) {
        if ((*it)->containsLocalPosition(position))
            return true;
    }
    return false;
}

bool FTCompoundBoundingShape::visibleInCamera(FTCamera* camera) {
    for (auto it = bounding_shapes_.begin(); it != bounding_shapes_.end(); ++it) {
        if ((*it)->visibleInCamera(camera))
            return true;
    }
    return false;
}

NS_FT_END