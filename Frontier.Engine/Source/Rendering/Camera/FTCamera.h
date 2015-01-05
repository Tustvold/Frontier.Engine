#pragma once
#include <glm/glm.hpp>
#include <FTObject.h>
#include <Util/FTRect.h>

// The base class for all cameras
// Contains some properties common to all cameras
class FTCamera : public FTObject {
public:

	FTCamera() : near_clipping_plane_(0.1f), far_clipping_plane_(10000.0f), projection_matrix_dirty_(true), view_matrix_dirty_(true) {

	}

	virtual const glm::mat4& getViewMatrix() const = 0;

	virtual const glm::mat4& getProjectionMatrix() const = 0;

	virtual const glm::mat4& getViewProjectionMatrix() const = 0;

	virtual void preDraw() = 0;

	virtual bool testBoundingBox(glm::vec3& center, glm::vec3& halfextents) const = 0;

	void setScreenRect(const FTRect<int>& screen_rect) {
		screen_rect_ = screen_rect;
		projection_matrix_dirty_ = true;
	}

	void setClippingPlanes(float near_plane, float far_plane) {
		projection_matrix_dirty_ = true;
		near_clipping_plane_ = near_plane;
		far_clipping_plane_ = far_plane;
	}

protected:
	FTRect<int> screen_rect_;
	float near_clipping_plane_;
	float far_clipping_plane_;
	bool projection_matrix_dirty_;
	bool view_matrix_dirty_;
};
