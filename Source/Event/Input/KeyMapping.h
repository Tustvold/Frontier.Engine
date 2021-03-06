#pragma once
#include "KeyboardDelegate.h"
#include <vector>

NS_FT_BEGIN

class KeyMapping : public KeyboardDelegate {
public:
    explicit KeyMapping() : pressed_count_(0) {
        this->setKeyboardDelegatePriority(DEFAULT_KEYBOARD_INPUT_PRIORITY * 2);
        this->setSwallowsEvents(false);
    }

    bool isPressed() const {
        return pressed_count_ != 0;
    }

    bool onKeyPressed(const KeyPressedEvent& event) override;
    void onKeyRelease(const KeyReleasedEvent& event) override;
    bool getKeyboardDelegateEnabled() const override;

    void addMapping(int mapped_key, int mods = 0);

    bool hasMapping(int mapped_key, int mods);

    bool checkEvent(const KeyPressedEvent& event) {
        return hasMapping(event.key_, event.mods_);
    }

    bool checkEvent(const KeyRepeatEvent& event) {
        return hasMapping(event.key_, event.mods_);
    }

    bool checkEvent(const KeyReleasedEvent& event) {
        return hasMapping(event.key_, event.mods_);
    }

    template <typename X, typename Y>
    void registerOnPressDelegate(Y* obj, void (X::*func)()) {
        on_pressed_.Connect(obj, func);
    }

    template <typename X, typename Y>
    void unregisterOnPressDelegate(Y* obj, void (X::*func)()) {
        on_pressed_.Disconnect(obj, func);
    }

    template <typename X, typename Y>
    void registerOnReleaseDelegate(Y* obj, void (X::*func)()) {
        on_released_.Connect(obj, func);
    }

    template <typename X, typename Y>
    void unregisterOnReleaseDelegate(Y* obj, void (X::*func)()) {
        on_released_.Disconnect(obj, func);
    }

private:
    int pressed_count_;

    // We use a vector as in the majority of cases there will only be 1 or 2 mapped keys
    std::vector<std::pair<int,int>> mapped_keys_;
    
    Gallant::Signal0<> on_pressed_;
    Gallant::Signal0<> on_released_;
};

NS_FT_END