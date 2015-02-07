#include "FTCameraFPS.h"
#include <Util/FTInputManager.h>
#include <Frontier.h>
#define _USE_MATH_DEFINES
#include <math.h>

FTCameraFPS::FTCameraFPS() : move_speed_(15.0f), rotation_speed_(0.005f) {
	FTInputManager::getSharedInstance()->getButtonHeldEventHandler()->Connect(this, &FTCameraFPS::keyHeld);
	FTInputManager::getSharedInstance()->getCursorMovedEventHandler()->Connect(this, &FTCameraFPS::cursorPosChange);
}


FTCameraFPS::~FTCameraFPS() {
}

void FTCameraFPS::keyHeld(KeyName key, float dt) {
	update_view_frustrum_ = true; // Quick hacky implementation of disabling frustrum updates TODO: add better implementation
	switch (key) {
		case KeyNameForward:
			position_ += look_direction_ * dt * move_speed_;
			view_matrix_dirty_ = true;
			break;

		case KeyNameBackward:
			position_ -= look_direction_ * dt * move_speed_;
			view_matrix_dirty_ = true;
			break;

		case KeyNameLeft:
			position_ -= right_vector_ * dt * move_speed_;
			view_matrix_dirty_ = true;
			break;

		case KeyNameRight:
			position_ += right_vector_ * dt * move_speed_;
			view_matrix_dirty_ = true;
			break;

		case KeyNameUp:
			position_.y += dt * move_speed_;
			view_matrix_dirty_ = true;
			break;

		case KeyNameDown:
			position_.y -= dt * move_speed_;
			view_matrix_dirty_ = true;
			break;
		case KeyNameFreezeFrustrum:
			update_view_frustrum_ = false;
			break;

		default:
			break;
	}
}

void FTCameraFPS::cursorPosChange(float x, float y) {
	FTLOG("%f %f", rotation_euler_radians.x, rotation_euler_radians.y);

	rotation_euler_radians.x += x * rotation_speed_;
	rotation_euler_radians.y += y * rotation_speed_;

	if (rotation_euler_radians.y > M_PI / 2.0f)
		rotation_euler_radians.y = (float)M_PI / 2.0f;
	else if (rotation_euler_radians.y < -M_PI / 2.0f)
		rotation_euler_radians.y = -(float)M_PI / 2.0f;


	rotation_dirty_ = true;
	view_matrix_dirty_ = true;
}
