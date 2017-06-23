#include "CompoundBoundingShape.h"

NS_FT_BEGIN

CompoundBoundingShape::CompoundBoundingShape() {
}

CompoundBoundingShape::CompoundBoundingShape(const std::vector<std::shared_ptr<BoundingShape>>& shapes) : bounding_shapes_(shapes) {

}

CompoundBoundingShape::CompoundBoundingShape(std::vector<std::shared_ptr<BoundingShape>>&& shapes) : bounding_shapes_(std::move(shapes)) {

}

void CompoundBoundingShape::onAddedToNode(Node* node) {
    for (auto it = bounding_shapes_.begin(); it != bounding_shapes_.end(); ++it) {
        (*it)->onAddedToNode(node);
    }
}

void CompoundBoundingShape::visit() {
    for (auto it = bounding_shapes_.begin(); it != bounding_shapes_.end(); ++it) {
        (*it)->visit();
    }
}

bool CompoundBoundingShape::containsMousePosition(const glm::vec2& mouse_pos) {
    for (auto it = bounding_shapes_.begin(); it != bounding_shapes_.end(); ++it) {
        if ((*it)->containsMousePosition(mouse_pos))
            return true;
    }
    return false;
}

bool CompoundBoundingShape::containsLocalPosition(const glm::vec3& position) {
    for (auto it = bounding_shapes_.begin(); it != bounding_shapes_.end(); ++it) {
        if ((*it)->containsLocalPosition(position))
            return true;
    }
    return false;
}

bool CompoundBoundingShape::visibleInCamera(Camera* camera) {
    for (auto it = bounding_shapes_.begin(); it != bounding_shapes_.end(); ++it) {
        if ((*it)->visibleInCamera(camera))
            return true;
    }
    return false;
}

NS_FT_END