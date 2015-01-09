#pragma once

#include "FTTransformPosition.h"
#include "FTTransformScale.h"
#include "FTTransformRotation.h"
#include "FTCompositeTransform.h"

class FTTransformPositionScaleRotation : public FTCompositeTransform3<FTTransformPosition, FTTransformRotation, FTTransformScale> {
public:
	FTTransformPositionScaleRotation() : FTCompositeTransform3(new FTTransformPosition(), new FTTransformRotation(), new FTTransformScale()) {
		transform1_->release();
		transform2_->release();
		transform3_->release();
	}

	void setPosition(const glm::vec3 pos) {
		transform1_->setPosition(pos);
	}

	void setRotationDegrees(const glm::vec3 pos) {
		transform2_->setRotationDegrees(pos);
	}

	void setRotationRadians(const glm::vec3 pos) {
		transform2_->setRotationRadians(pos);
	}

	void setScale(const glm::vec3 pos) {
		transform3_->setScale(pos);
	}
};
