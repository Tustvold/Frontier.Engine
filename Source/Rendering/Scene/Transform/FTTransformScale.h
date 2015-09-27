#pragma once
#include <Rendering/Scene/Transform/FTTransform.h>


class FTTransformScale : public FTTransform {
public:
    FTTransformScale() : scale_(0, 0, 0) {

    }

    void setScale(const glm::vec3& scale) {
        scale_ = scale;
        transform_matrix.getData()[0][0] = scale.x;
        transform_matrix.getData()[1][1] = scale.y;
        transform_matrix.getData()[2][2] = scale.z;
        transform_dirty_ = true;
    }

    const glm::vec3& getScale() {
        return scale_;
    }

protected:
    glm::vec3 scale_;
};
