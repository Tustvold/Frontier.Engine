#include <Event/Input/FTKeyboardDelegate.h>
#include <FTEngine.h>
#include "FTInputManager.h"

NS_FT_BEGIN

void FTKeyboardDelegate::setKeyboardDelegatePriority(uint32_t priority) {
    priority_ = priority;
}

NS_FT_END