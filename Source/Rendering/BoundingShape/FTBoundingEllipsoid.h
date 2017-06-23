#pragma once
#include "FTBoundingShape.h"

NS_FT_BEGIN

class FTBoundingEllipsoid : public FTBoundingShape {
public:
    explicit FTBoundingEllipsoid(const glm::vec3& radii);

    void visit() override;
    bool containsLocalPosition(const glm::vec3& position) override;
    bool visibleInCamera(FTCamera* camera) override;
    glm::vec3 getLayoutSize() const override;
    glm::vec3 computeLocalOffset(const glm::vec3& anchor_point) override;

    const glm::vec3& getAABCenter() const {
        return aab_center_;
    }

    const glm::vec3& getAABHalfExtents() const {
        return aab_half_extents_;
    }
protected:
    glm::vec3 radii_;

    glm::vec3 aab_center_;
    glm::vec3 aab_half_extents_;
};

NS_FT_END