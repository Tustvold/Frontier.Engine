#pragma once
#include <Event/Mouse/FTMouseEventDispatcher.h>

#define DEFAULT_MOUSE_INPUT_PRIORITY 128


// A targeted delegate to facilitate UI 
class FTMouseDelegate {
    friend class FTInputManager;
public:
    explicit FTMouseDelegate() : priority_(DEFAULT_MOUSE_INPUT_PRIORITY), is_added_(false) {

    }

    virtual ~FTMouseDelegate() {
    }

    // Return true to swallow the event and receive further calls regarding it
    virtual bool onMouseDown(const FTMouseButtonPressedEvent& event) = 0;
    virtual void onMouseDrag(const FTMouseMoveEvent&, int mouse_button) = 0;
    virtual void onMouseRelease(const FTMouseButtonReleasedEvent& event) = 0;


    virtual bool getMouseDelegateEnabled() const = 0;

    void setMouseDelegatePriority(int priority);

    int getMouseDelegatePriority() const {
        return priority_;
    }

    bool getMouseDelegateAdded() const {
        return is_added_;
    }

private:
    int priority_;
    bool is_added_;
};
