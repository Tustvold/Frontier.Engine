#pragma once
#include "FTKeyboardDelegate.h"
#include <vector>

class FTKeyMapping : public FTKeyboardDelegate {
public:
    explicit FTKeyMapping() : pressed_count_(0) {
    }

    bool isPressed() const {
        return pressed_count_ != 0;
    }

    bool onKeyPressed(const FTKeyPressedEvent& event) override;
    void onKeyRelease(const FTKeyReleasedEvent& event) override;
    bool getKeyboardDelegateEnabled() const override;

    void addMapping(int mapped_key, int mods = 0);

    bool hasMapping(int mapped_key, int mods);

    bool checkEvent(const FTKeyPressedEvent& event) {
        return hasMapping(event.key_, event.mods_);
    }

    bool checkEvent(const FTKeyRepeatEvent& event) {
        return hasMapping(event.key_, event.mods_);
    }

    bool checkEvent(const FTKeyReleasedEvent& event) {
        return hasMapping(event.key_, event.mods_);
    }

private:
    int pressed_count_;

    // We use a vector as in the majority of cases there will only be 1 or 2 mapped keys
    std::vector<std::pair<int,int>> mapped_keys_;

};
