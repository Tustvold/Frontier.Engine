#pragma once

#include "TransformPosition.h"
#include "TransformScale.h"
#include "TransformRotation.h"
#include "CompositeTransform.h"

NS_FT_BEGIN

class TransformPositionScaleRotation : public CompositeTransform3<TransformPosition, TransformRotation, TransformScale> {
public:
    TransformPositionScaleRotation() : CompositeTransform3() {

    }

    void setPosition(const glm::vec3 pos) {
        transform1_->setPosition(pos);
    }

    void setRotationQuaternion(const glm::quat quat) {
        transform2_->setRotationQuaterion(quat);
    }

    void setScale(const glm::vec3& pos) {
        transform3_->setScale(pos);
    }

    const glm::vec3& getPosition() const {
        return transform1_->getPosition();
    }

    const glm::quat& getRotationQuaternion() const {
        return transform2_->getRotationQuaternion();
    }

    const glm::vec3& getScale() const {
        return transform3_->getScale();
    }
};

NS_FT_END