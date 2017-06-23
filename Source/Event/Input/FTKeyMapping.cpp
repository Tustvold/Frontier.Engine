#include "FTKeyMapping.h"

NS_FT_BEGIN

bool FTKeyMapping::onKeyPressed(const FTKeyPressedEvent& event) {
    if (!checkEvent(event))
        return false;

    FTAssert(pressed_count_ >= 0, "Invalid Pressed count");

    pressed_count_++;

    if (pressed_count_ == 1)
        on_pressed_();

    return true;
}


void FTKeyMapping::onKeyRelease(const FTKeyReleasedEvent& event) {
    pressed_count_--;
    FTAssert(pressed_count_ >= 0, "Invalid Pressed count");

    if (pressed_count_ == 0)
        on_released_();
}

bool FTKeyMapping::getKeyboardDelegateEnabled() const {
    return true;
}

void FTKeyMapping::addMapping(int mapped_key, int mods) {
    if (hasMapping(mapped_key, mods))
        return;
    mapped_keys_.push_back(std::make_pair(mapped_key, mods));
}

bool FTKeyMapping::hasMapping(int mapped_key, int mods) {
    for (auto it = mapped_keys_.begin(); it != mapped_keys_.end(); ++it) {
        if (it->first == mapped_key && (it->second & mods) == it->second)
            return true;
    }
    return false;
}

NS_FT_END