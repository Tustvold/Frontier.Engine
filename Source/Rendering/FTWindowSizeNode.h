#pragma once

#include <Rendering/FTNode.h>
#include <FTEngine.h>

NS_FT_BEGIN

// An FTNode with the same size as the window
// Useful for positioning 2D elements relative to the window borders
// For example setting the anchor point to (-0.5,-0.5) would position
// children relative to the center of the screen
//
// This will automatically update if the window is resized
class FTWindowSizeNode : public FTNode {
public:

    FTWindowSizeNode() {
        this->setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(FTEngine::getWindowSize(),0)));
        FTEngine::getEventManager()->registerDelegate<FTWindowEventDispatcher>(this, &FTWindowSizeNode::screensizeChanged);
    }

    ~FTWindowSizeNode() {
        FTEngine::getEventManager()->unregisterDelegate<FTWindowEventDispatcher>(this, &FTWindowSizeNode::screensizeChanged);
    }

private:

    void screensizeChanged(const FTWindowResizeEvent& event) {
        this->setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(event.width_, event.height_, 0)));

    }
};

NS_FT_END