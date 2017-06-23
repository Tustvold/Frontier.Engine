#pragma once

#include <Rendering/Node.h>
#include <Engine.h>

NS_FT_BEGIN

// An Node with the same size as the window
// Useful for positioning 2D elements relative to the window borders
// For example setting the anchor point to (-0.5,-0.5) would position
// children relative to the center of the screen
//
// This will automatically update if the window is resized
class WindowSizeNode : public Node {
public:

    WindowSizeNode() {
        this->setBoundingShape(std::make_unique<BoundingCuboid>(glm::vec3(Engine::getWindowSize(),0)));
        Engine::getEventManager()->registerDelegate<WindowEventDispatcher>(this, &WindowSizeNode::screensizeChanged);
    }

    ~WindowSizeNode() {
        Engine::getEventManager()->unregisterDelegate<WindowEventDispatcher>(this, &WindowSizeNode::screensizeChanged);
    }

private:

    void screensizeChanged(const WindowResizeEvent& event) {
        this->setBoundingShape(std::make_unique<BoundingCuboid>(glm::vec3(event.width_, event.height_, 0)));

    }
};

NS_FT_END