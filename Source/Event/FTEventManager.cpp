#include "FTEventManager.h"
#include <Frontier.h>

FTEventManager::FTEventManager() {
    
}

FTEventManager::~FTEventManager() {
    FTLOG("FTEventManager destroyed");
    event_dispatchers_.clear();
}
