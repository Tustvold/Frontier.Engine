#pragma once
#include <Rendering/Mesh/FTIndexedMesh.h>
#include <Rendering/Scene/Transform/FTTransformUtil.h>

class FTCube : public FTIndexedMesh<FTVertexColor,uint16_t> {
public:
	explicit FTCube(const glm::vec3 face_colors[6]);
	~FTCube();

	virtual FTTransform* getTransform() override {
		return transform_;
	}

	void setPosition(const glm::vec3& position) {
		transform_->setPosition(position);
	}

protected:
	FTTransformPositionScaleRotation* transform_;
};
