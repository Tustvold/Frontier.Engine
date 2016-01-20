#pragma once
#include <Rendering/Transform/FTTransform.h>


class FTTransformScale : public FTTransform {
public:
    FTTransformScale() : scale_(1, 1, 1) {
        transform_dirty_ = false;
    }

    void setScale(const glm::vec3& scale) {
        scale_ = scale;
        transform_matrix[0][0] = scale.x;
        transform_matrix[1][1] = scale.y;
        transform_matrix[2][2] = scale.z;
        transform_dirty_ = true;
    }

    const glm::vec3& getScale() {
        return scale_;
    }

protected:
    glm::vec3 scale_;
};
