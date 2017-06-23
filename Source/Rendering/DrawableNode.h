#pragma once
#include <Rendering/ShaderNode.h>

NS_FT_BEGIN

// A ShaderNode which renders a provided Drawable
template <typename ShaderProgram>
class DrawableNode : public ShaderNode {
public:
    explicit DrawableNode(std::unique_ptr<Drawable> drawable, VertexShaderProgram* program = getShaderUtil<VertexShaderProgram>()) : ShaderNode(), drawable_(std::move(drawable)) {

    }

    virtual ~DrawableNode() {

    }

    virtual void draw() override {
        drawable_->draw();
    }

protected:
    std::unique_ptr<Drawable> drawable_;
};

NS_FT_END