#pragma once
#include <Rendering/Scene/FTNode.h>

// A FTNode which renders a provided FTDrawable
class FTDrawableNode : public FTNode {
public:
	FTDrawableNode(FTTransform *transform, FTVertexShaderProgram* shader, FTDrawable* drawable) : FTNode(transform, shader), drawable_(drawable) {
		drawable_->retain();
	}

	virtual ~FTDrawableNode() {
		drawable_->release();
	}

	virtual void draw() override {
		drawable_->draw();
	}

protected:
	FTDrawable* drawable_;
};