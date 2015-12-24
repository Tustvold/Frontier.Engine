#pragma once

#include "FTTransformPosition.h"
#include "FTTransformScale.h"
#include "FTTransformRotation.h"
#include "FTCompositeTransform.h"


class FTTransformPositionScaleRotation : public FTCompositeTransform3<FTTransformPosition, FTTransformRotation, FTTransformScale> {
public:
    FTTransformPositionScaleRotation() : FTCompositeTransform3() {

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
