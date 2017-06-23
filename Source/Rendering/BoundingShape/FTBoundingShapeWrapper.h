#pragma once
#include <Frontier.h>
#include "FTBoundingShape.h"

NS_FT_BEGIN

class FTBoundingShapeWrapper : public FTBoundingShape {
public:
    explicit FTBoundingShapeWrapper(const std::shared_ptr<FTNode>& wrapped);

    glm::vec3 computeLocalOffset(const glm::vec3& anchor_point) override;

    bool visibleInCamera(FTCamera* camera) override;

    glm::vec3 getLayoutSize() const override;

    // NB Local coordinates of the node this shape is attached to
    // not the local coordinates of the node owning the wrapped shape
    bool containsLocalPosition(const glm::vec3& position) override;

    bool containsMousePosition(const glm::vec2& mouse_pos) override;
protected:
    std::shared_ptr<FTNode> wrapped_;
};

NS_FT_END