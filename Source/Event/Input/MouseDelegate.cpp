#include <Event/Input/MouseDelegate.h>
#include <Engine.h>
#include "InputManager.h"

NS_FT_BEGIN

void MouseDelegate::setMouseDelegatePriority(uint32_t priority) {
    priority_ = priority;
}

NS_FT_END