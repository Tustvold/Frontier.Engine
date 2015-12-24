#pragma once

#include <Rendering/FTNode.h>
#include <FTEngine.h>

// An FTNode with the same size as the window
// Useful for positioning 2D elements relative to the window borders
// For example setting the anchor point to (-0.5,-0.5) would position
// children relative to the center of the screen
//
// This will automatically update if the window is resized
class FTWindowSizeNode : public FTNode {
public:

    FTWindowSizeNode() {
        this->setSize(FTEngine::getWindowSize());
        FTEngine::getEventManager()->registerDelegate<FTWindowEventDispatcher>(this, &FTWindowSizeNode::screensizeChanged);
    }

    ~FTWindowSizeNode() {
        FTEngine::getEventManager()->unregisterDelegate<FTWindowEventDispatcher>(this, &FTWindowSizeNode::screensizeChanged);
    }

private:

    void screensizeChanged(const FTWindowResizeEvent& event) {
        this->setSize(glm::vec2(event.width_, event.height_));
    }
};
