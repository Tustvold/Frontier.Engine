#pragma once
#include <Rendering/Transform/Transform.h>

NS_FT_BEGIN

class TransformPosition : public Transform {
public:

    TransformPosition() : position_(0, 0, 0) {
        transform_dirty_ = false;
    }

    void setPosition(const glm::vec3& position) {
        position_ = position;
        transform_matrix[3][0] = position.x;
        transform_matrix[3][1] = position.y;
        transform_matrix[3][2] = position.z;
        transform_dirty_ = true;
    }

    const glm::vec3& getPosition() const {
        return position_;
    }

protected:
    glm::vec3 position_;
};

NS_FT_END