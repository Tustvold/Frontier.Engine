#pragma once
#include <Rendering/FTShaderNode.h>

NS_FT_BEGIN

// A FTShaderNode which renders a provided FTDrawable
template <typename ShaderProgram>
class FTDrawableNode : public FTShaderNode {
public:
    explicit FTDrawableNode(std::unique_ptr<FTDrawable> drawable, FTVertexShaderProgram* program = getShaderUtil<FTVertexShaderProgram>()) : FTShaderNode(), drawable_(std::move(drawable)) {

    }

    virtual ~FTDrawableNode() {

    }

    virtual void draw() override {
        drawable_->draw();
    }

protected:
    std::unique_ptr<FTDrawable> drawable_;
};

NS_FT_END