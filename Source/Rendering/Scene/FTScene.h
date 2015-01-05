#pragma once
#include <FTArray.h>
#include <Rendering/Scene/FTView.h>

// The root object of every scene, contains a list of the FTLayers to be drawn
class FTScene : public FTObject {
public:
	explicit FTScene() : views_(new FTArray<FTView>()) {

	}

	virtual ~FTScene() {
		views_->release();
	}

	virtual void draw() {
		for (auto it = views_->begin(); it != views_->end(); ++it) {
			(*it)->draw();
		}
	}

	void addView(FTView* layer) {
		views_->add(layer);
	}

private:
	FTArray<FTView>* views_;
};
