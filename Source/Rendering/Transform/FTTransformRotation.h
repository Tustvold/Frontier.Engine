#pragma once
#include <Rendering/Transform/FTTransform.h>
#include <glm/gtx/quaternion.hpp>

class FTTransformRotation : public FTTransform {
public:
    virtual bool updateMatrices() override {
        if (transform_dirty_) {
            transform_matrix = glm::toMat4(rotation_quat_);
            transform_dirty_ = false;
            return true;
        }
        return false;
    }

    void setRotationQuaterion(const glm::quat& quat) {
        rotation_quat_ = quat;
        transform_dirty_ = true;
    }

    const glm::quat& getRotationQuaternion() const {
        return rotation_quat_;
    }

protected:
    glm::quat rotation_quat_;
};
