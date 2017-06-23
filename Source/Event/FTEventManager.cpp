#include "FTEventManager.h"
#include <Frontier.h>

NS_FT_BEGIN

FTEventManager::FTEventManager() {

}

FTEventManager::~FTEventManager() {
    FTLOG("FTEventManager destroyed");
    event_dispatchers_.clear();
}

NS_FT_END