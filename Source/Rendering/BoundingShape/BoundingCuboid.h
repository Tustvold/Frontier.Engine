#pragma once
#include "BoundingShape.h"

NS_FT_BEGIN

class BoundingCuboid : public BoundingShape {
public:
    explicit BoundingCuboid(const glm::vec3& size);
    BoundingCuboid(const glm::vec3& origin, const glm::vec3& size);
    virtual ~BoundingCuboid();
    
    void visit() override;
    bool visibleInCamera(Camera* camera) override;

    glm::vec3 computeLocalOffset(const glm::vec3& anchor_point) override;

    bool containsLocalPosition(const glm::vec3& position) override;

    glm::vec3 getLayoutSize() const override {
        return size_;
    }

    void setSize(const glm::vec3& size) {
        size_ = size;
        dirty_ = true;
    }

    void setOrigin(const glm::vec3& origin) {
        origin_ = origin;
        dirty_ = true;
    }

    const glm::vec3& getAABCenter() const {
        return aab_center_;
    }

    const glm::vec3& getAABHalfExtents() const {
        return aab_half_extents_;
    }

protected:
    glm::vec3 origin_;
    glm::vec3 size_;

    glm::vec3 aab_center_;
    glm::vec3 aab_half_extents_;
};

NS_FT_END