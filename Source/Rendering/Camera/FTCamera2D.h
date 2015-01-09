#pragma once

#include <Rendering/Camera/FTCamera.h>
#include <Util/FTAlignedData.h>
#include <glm/gtc/matrix_transform.hpp>

class FTCamera2D : public FTCamera{
public:
	FTCamera2D() {
		setClippingPlanes(0, 1);
	}

	~FTCamera2D() {

	}

	const glm::mat4& getViewMatrix() const override {
		return view_matrix.getConstData();
	}

	const glm::mat4& getProjectionMatrix() const override {
		return projection_matrix_.getConstData();
	}

	const glm::mat4& getViewProjectionMatrix() const override {
		return projection_matrix_.getConstData();
	}

	void preDraw() override {
		FTCamera::preDraw();
		if (projection_matrix_dirty_) {
			projection_matrix_ = glm::ortho<float>(0, (float)screen_rect_.width_, 0, (float)screen_rect_.height_, near_clipping_plane_, far_clipping_plane_);
			projection_matrix_dirty_ = false;
		}
	}

	bool testBoundingBox(glm::vec3& center, glm::vec3& halfextents) const override {
		return true;
	}

private:
	FTAlignedData<glm::mat4> projection_matrix_;
	FTAlignedData<glm::mat4> view_matrix;
};
