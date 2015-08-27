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

	virtual bool getDirty() {
		return transform_dirty_;
	}

protected:

	// This matrix should only be accessed and altered from the draw thread
	FTAlignedData<glm::mat4> transform_matrix;
	bool transform_dirty_;
};
