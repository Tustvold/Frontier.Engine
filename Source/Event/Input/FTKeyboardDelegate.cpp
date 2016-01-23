#include <Event/Input/FTKeyboardDelegate.h>
#include <FTEngine.h>
#include "FTInputManager.h"

void FTKeyboardDelegate::setKeyboardDelegatePriority(int priority) {
    priority_ = priority;
    if (is_added_)
        FTEngine::getInputManager()->keyboardDelegatePriorityChange(this);
}