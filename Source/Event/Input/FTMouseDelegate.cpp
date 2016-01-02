#include <Event/Input/FTMouseDelegate.h>
#include <FTEngine.h>
#include "FTInputManager.h"

void FTMouseDelegate::setMouseDelegatePriority(int priority) {
    priority_ = priority;
    if (is_added_)
        FTEngine::getInputManager()->mouseDelegatePriorityChange(this);
}