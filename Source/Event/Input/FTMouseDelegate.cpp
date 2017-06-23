#include <Event/Input/FTMouseDelegate.h>
#include <FTEngine.h>
#include "FTInputManager.h"

NS_FT_BEGIN

void FTMouseDelegate::setMouseDelegatePriority(uint32_t priority) {
    priority_ = priority;
}

NS_FT_END