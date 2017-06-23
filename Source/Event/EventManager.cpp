#include "EventManager.h"
#include <Frontier.h>

NS_FT_BEGIN

EventManager::EventManager() {

}

EventManager::~EventManager() {
    FTLOG("EventManager destroyed");
    event_dispatchers_.clear();
}

NS_FT_END