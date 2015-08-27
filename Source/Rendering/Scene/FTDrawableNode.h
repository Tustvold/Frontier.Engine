#pragma once
#include <Rendering/Scene/FTNode.h>

// A FTNode which renders a provided FTDrawable
template <typename Transform, typename ShaderProgram>
class FTDrawableNode : public FTNode<Transform, ShaderProgram> {
public:
	explicit FTDrawableNode(std::unique_ptr<FTDrawable> drawable) : FTNode(), drawable_(std::move(drawable)) {

	}

	virtual ~FTDrawableNode() {

	}

	virtual void draw() override {
		drawable_->draw();
	}

protected:
	std::unique_ptr<FTDrawable> drawable_;
};
