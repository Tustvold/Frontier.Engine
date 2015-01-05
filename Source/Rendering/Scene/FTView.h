#pragma once
#include <Rendering/Camera/FTCamera.h>
#include <Rendering/FTDrawable.h>

// Base class for all direct children of FTScene
// Manages a camera object and uses it to draw to a section of the screen
class FTView : public FTDrawable {
public:

	explicit FTView(FTCamera* camera, const FTRect<float>& layer_rect);

	virtual ~FTView();

	virtual void draw() override {
		camera_->preDraw();
	}

protected:
	FTCamera* camera_;

	// Screen rect in fractional values (i.e between 0 and 1)
	FTRect<float> layer_rect_;

	void screensizeChanged(float width, float height);
};
