#pragma once
#include <Event/Mouse/FTMouseEventDispatcher.h>

// A targeted delegate to facilitate UI 
class FTMouseDelegate {
public:
    explicit FTMouseDelegate(int priority) : priority_(priority) {

    }

    virtual ~FTMouseDelegate() {
    }

    // Return true to swallow the event and receive further calls regarding it
    virtual bool onMouseDown(const FTMouseButtonPressedEvent& event) = 0;
    virtual void onMouseDrag(const FTMouseMoveEvent&, int mouse_button) = 0;
    virtual void onMouseRelease(const FTMouseButtonReleasedEvent& event) = 0;

    // Return true to swallow the event
    virtual bool onMouseMove(const FTMouseMoveEvent& event) = 0;

    virtual bool getMouseDelegateEnabled() const = 0;

    int getPriority() const {
        return priority_;
    }

private:
    int priority_;
};
