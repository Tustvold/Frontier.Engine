#include <Event/Input/FTKeyboardDelegate.h>
#include <FTEngine.h>
#include "FTInputManager.h"

void FTKeyboardDelegate::setKeyboardDelegatePriority(uint32_t priority) {
    priority_ = priority;
}