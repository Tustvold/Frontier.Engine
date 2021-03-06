#pragma once
#include <Event/Mouse/MouseEventDispatcher.h>

#define DEFAULT_MOUSE_INPUT_PRIORITY 128

NS_FT_BEGIN

// A targeted delegate to facilitate UI 
class MouseDelegate {
    friend class InputManager;
public:
    explicit MouseDelegate() : priority_(DEFAULT_MOUSE_INPUT_PRIORITY), is_added_(false), swallows_events_(true) {

    }

    virtual ~MouseDelegate() {
    }

    // Return true to swallow the event and receive further calls regarding it
    virtual bool onMouseDown(const MouseButtonPressedEvent& event) = 0;
    virtual void onMouseDrag(const MouseMoveEvent&, int mouse_button) = 0;
    virtual void onMouseRelease(const MouseButtonReleasedEvent& event) = 0;


    virtual bool getMouseDelegateEnabled() const = 0;

    virtual void setMouseDelegatePriority(uint32_t priority);

    virtual uint32_t getMouseDelegatePriority() const {
        return priority_;
    }

    bool getMouseDelegateAdded() const {
        return is_added_;
    }


    void setSwallowsEvents(bool swallows_touches) {
        swallows_events_ = swallows_touches;
    }

    bool getSwallowsEvents() const {
        return swallows_events_;
    }

private:
    uint32_t priority_;
    bool is_added_;
    bool swallows_events_;
};

NS_FT_END