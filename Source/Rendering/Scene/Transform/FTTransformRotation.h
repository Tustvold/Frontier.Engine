#pragma once
#include <Rendering/Scene/Transform/FTTransform.h>

class FTTransformRotation : public FTTransform {
public:
	virtual void updateMatrices() override {
		if (transform_dirty_) {
			transform_matrix = glm::eulerAngleYXZ(rotation_euler_radians_.y, rotation_euler_radians_.x, rotation_euler_radians_.z);
			transform_dirty_ = false;
		}
	}

	void setRotationRadians(const glm::vec3& rotation) {
		rotation_euler_radians_ = rotation;
		transform_dirty_ = true;
	}

	void setRotationDegrees(const glm::vec3& rotation) {
		setRotationRadians(rotation * RAD2DEG);
	}

protected:
	glm::vec3 rotation_euler_radians_;
	
};