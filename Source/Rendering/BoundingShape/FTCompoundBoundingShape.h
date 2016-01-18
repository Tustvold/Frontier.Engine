#pragma once
#include <Frontier.h>
#include "FTBoundingShape.h"
#include <vector>

class FTCamera;
class FTNode;
    
class FTCompoundBoundingShape : public FTBoundingShape {
public:
    FTCompoundBoundingShape();
    explicit FTCompoundBoundingShape(const std::vector<std::shared_ptr<FTBoundingShape>>& shapes);
    explicit FTCompoundBoundingShape(std::vector<std::shared_ptr<FTBoundingShape>>&& shapes);

    void addBoundingShape(const std::shared_ptr<FTBoundingShape>& shape) {
        bounding_shapes_.push_back(shape);
    }

    void addBoundingShape(std::shared_ptr<FTBoundingShape>&& shape) {
        bounding_shapes_.push_back(std::move(shape));
    }

    void onAddedToNode(FTNode* node) override;
    void visit() override;
    bool containsMousePosition(const glm::vec2& mouse_pos) override;
    bool containsLocalPosition(const glm::vec3& position) override;
    bool visibleInCamera(FTCamera* camera) override;
protected:
    std::vector<std::shared_ptr<FTBoundingShape>> bounding_shapes_;
};