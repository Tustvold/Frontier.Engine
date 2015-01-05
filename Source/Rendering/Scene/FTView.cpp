#include "FTView.h"
#include <Rendering/FTDirector.h>

FTView::FTView(FTCamera* camera, const FTRect<float>& layer_rect) : camera_(camera), layer_rect_(layer_rect) {
	camera_->retain();
	glm::vec2 screensize = FTDirector::getSharedInstance()->getWindowSize();
	camera_->setScreenRect(FTRect<int>((int)(layer_rect.x_ * screensize.x), (int)(layer_rect.y_ * screensize.y), (int)(layer_rect.width_ * screensize.x), (int)(layer_rect.height_ * screensize.y)));
	FTDirector::getSharedInstance()->getWindowSizeChangeEventHandler()->Connect(this, &FTView::screensizeChanged);
}

FTView::~FTView() {
	camera_->release();
	FTDirector::getSharedInstance()->getWindowSizeChangeEventHandler()->Disconnect(this, &FTView::screensizeChanged);
}


void FTView::screensizeChanged(float width, float height) {
	camera_->setScreenRect(FTRect<int>((int)(layer_rect_.x_ * width), (int)(layer_rect_.y_ * height), (int)(layer_rect_.width_ * width), (int)(layer_rect_.height_ * height)));
}
