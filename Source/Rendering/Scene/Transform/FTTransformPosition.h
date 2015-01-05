#pragma once
#include <Rendering/Scene/Transform/FTTransform.h>

class FTTransformPosition : public FTTransform {
public:

	void setPosition(const glm::vec3& position) {
		transform_matrix.getData()[3][0] = position.x;
		transform_matrix.getData()[3][1] = position.y;
		transform_matrix.getData()[3][2] = position.z;
		transform_dirty_ = true;
	}

protected:
};
