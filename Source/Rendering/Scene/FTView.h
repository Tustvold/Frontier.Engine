#pragma once
#include <Rendering/Camera/FTCamera.h>
#include <Rendering/FTDrawable.h>

class IFTView : public FTDrawable {

};

// Base class for all direct children of FTScene
// Manages a camera object and uses it to draw to a section of the screen
template <typename Camera>
class FTView : public IFTView {
public:
	FTView(const std::shared_ptr<Camera>& camera, const FTRect<float>& layer_rect) : camera_(camera), layer_rect_(layer_rect) {
		glm::vec2 screensize = FTDirector::getSharedInstance()->getWindowSize();
		camera_->setScreenRect(FTRect<int>((int)(layer_rect.x_ * screensize.x), (int)(layer_rect.y_ * screensize.y), (int)(layer_rect.width_ * screensize.x), (int)(layer_rect.height_ * screensize.y)));
		FTDirector::getSharedInstance()->getWindowSizeChangeEventHandler()->Connect(this, &FTView::screensizeChanged);
	}

	virtual ~FTView() {
		FTDirector::getSharedInstance()->getWindowSizeChangeEventHandler()->Disconnect(this, &FTView::screensizeChanged);
	}

	virtual void draw() override {
		camera_->preDraw();
	}

protected:
	std::shared_ptr<Camera> camera_;

	// Screen rect in fractional values (i.e between 0 and 1)
	FTRect<float> layer_rect_;

	void screensizeChanged(float width, float height) {
		camera_->setScreenRect(FTRect<int>((int)(layer_rect_.x_ * width), (int)(layer_rect_.y_ * height), (int)(layer_rect_.width_ * width), (int)(layer_rect_.height_ * height)));
	}
};
