#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <FTObject.h>
#include <Util/FTAlignedData.h>

// Creates and manages a transform
class FTTransform : public FTObject {
public:
	FTTransform() {
		transform_matrix = glm::mat4();
	}

	virtual ~FTTransform() {
	}


	// This matrix should only be accessed and altered from the draw thread
	const glm::mat4& getTransformMatrix() {
		updateMatrices();
		return transform_matrix.getConstData();
	}

	virtual void updateMatrices() {
		transform_dirty_ = false;
	}

	/*void updateMatrices() {

		if (transform_matrix_dirty_) {
			//pthread_mutex_lock(&data_mutex_);
			if (rotation_matrix_dirty_) {

				rotation_matrix_ = glm::eulerAngleYXZ(rotation_euler_radians_.y, rotation_euler_radians_.x, rotation_euler_radians_.z);
				rotation_matrix_dirty_ = false;
				transform_matrix_dirty_ = true;
			}

			transform_matrix = translation_matrix_.getData() * rotation_matrix_.getData() * scale_matrix_.getData();
			transform_matrix_dirty_ = false;
			//pthread_mutex_unlock(&data_mutex_);
		}

	}*/

	virtual bool getDirty() {
		return transform_dirty_;
	}

protected:

	// This matrix should only be accessed and altered from the draw thread
	FTAlignedData<glm::mat4> transform_matrix;
	bool transform_dirty_;
};
