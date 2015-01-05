#pragma once
#include <Rendering/Scene/Transform/FTTransform.h>


class FTTransformScale : public FTTransform {
public:
	void setScale(const glm::vec3& scale) {
		transform_matrix.getData()[0][0] = scale.x;
		transform_matrix.getData()[1][1] = scale.y;
		transform_matrix.getData()[2][2] = scale.z;
		transform_dirty_ = true;
	}

protected:
};