#pragma once
#include <Util/FTInputManager.h>
#include "FTCamera3D.h"

class FTCameraFPS : public FTCamera3D {
public:
	explicit FTCameraFPS();
	~FTCameraFPS();


private:

	float move_speed_;
	float rotation_speed_;

	void keyHeld(KeyName, float dt);
	void cursorPosChange(float x, float y);
};
