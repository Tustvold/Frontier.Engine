#pragma once
#include <Rendering/FTShaderNode.h>

// A FTShaderNode which renders a provided FTDrawable
template <typename ShaderProgram>
class FTDrawableNode : public FTShaderNode<ShaderProgram> {
public:
    explicit FTDrawableNode(std::unique_ptr<FTDrawable> drawable) : FTShaderNode(), drawable_(std::move(drawable)) {

    }

    virtual ~FTDrawableNode() {

    }

    virtual void draw() override {
        drawable_->draw();
    }

protected:
    std::unique_ptr<FTDrawable> drawable_;
};
