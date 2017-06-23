#include <Event/Input/KeyboardDelegate.h>
#include <Engine.h>
#include "InputManager.h"

NS_FT_BEGIN

void KeyboardDelegate::setKeyboardDelegatePriority(uint32_t priority) {
    priority_ = priority;
}

NS_FT_END