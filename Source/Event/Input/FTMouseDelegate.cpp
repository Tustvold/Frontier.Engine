#include <Event/Input/FTMouseDelegate.h>
#include <FTEngine.h>
#include "FTInputManager.h"

void FTMouseDelegate::setMouseDelegatePriority(uint32_t priority) {
    priority_ = priority;
}