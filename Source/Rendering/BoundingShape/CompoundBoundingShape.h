#pragma once
#include <Frontier.h>
#include "BoundingShape.h"
#include <vector>

NS_FT_BEGIN

class Camera;
class Node;
    
class CompoundBoundingShape : public BoundingShape {
public:
    CompoundBoundingShape();
    explicit CompoundBoundingShape(const std::vector<std::shared_ptr<BoundingShape>>& shapes);
    explicit CompoundBoundingShape(std::vector<std::shared_ptr<BoundingShape>>&& shapes);

    void addBoundingShape(const std::shared_ptr<BoundingShape>& shape) {
        bounding_shapes_.push_back(shape);
    }

    void addBoundingShape(std::shared_ptr<BoundingShape>&& shape) {
        bounding_shapes_.push_back(std::move(shape));
    }

    void onAddedToNode(Node* node) override;
    void visit() override;
    bool containsMousePosition(const glm::vec2& mouse_pos) override;
    bool containsLocalPosition(const glm::vec3& position) override;
    bool visibleInCamera(Camera* camera) override;
protected:
    std::vector<std::shared_ptr<BoundingShape>> bounding_shapes_;
};

NS_FT_END