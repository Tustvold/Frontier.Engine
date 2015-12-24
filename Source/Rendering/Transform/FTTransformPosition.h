#pragma once
#include <Rendering/Transform/FTTransform.h>

class FTTransformPosition : public FTTransform {
public:

    FTTransformPosition() : position_(0, 0, 0) {

    }

    void setPosition(const glm::vec3& position) {
        position_ = position;
        transform_matrix.getData()[3][0] = position.x;
        transform_matrix.getData()[3][1] = position.y;
        transform_matrix.getData()[3][2] = position.z;
        transform_dirty_ = true;
    }

    const glm::vec3& getPosition() const {
        return position_;
    }

protected:
    glm::vec3 position_;
};
