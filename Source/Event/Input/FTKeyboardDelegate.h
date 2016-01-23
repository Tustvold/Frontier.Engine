#pragma once
#include <Event/Mouse/FTMouseEventDispatcher.h>
#include <Event/Keyboard/FTKeyboardEventDispatcher.h>

#define DEFAULT_KEYBOARD_INPUT_PRIORITY 128

// A targeted delegate to facilitate UI 
class FTKeyboardDelegate {
    friend class FTInputManager;
public:
    explicit FTKeyboardDelegate() : priority_(DEFAULT_KEYBOARD_INPUT_PRIORITY), is_added_(false) {

    }

    virtual ~FTKeyboardDelegate() {
    }

    virtual bool onKeyPressed(const FTKeyPressedEvent& event) = 0;

    virtual void onKeyRepeat(const FTKeyRepeatEvent& event) {
        
    }

    virtual void onKeyRelease(const FTKeyReleasedEvent& event) {
        
    }

    virtual bool getKeyboardDelegateEnabled() const = 0;

    void setKeyboardDelegatePriority(int priority);

    int getKeyboardDelegatePriority() const {
        return priority_;
    }

    bool getKeyboardDelegateAdded() const {
        return is_added_;
    }

private:
    int priority_;
    bool is_added_;
};
