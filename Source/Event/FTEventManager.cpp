#include "FTEventManager.h"
#include <Frontier.h>

static FTEventManager *s_sharedInstance;
static bool s_initialized = false;

FTEventManager* FTEventManager::getSharedInstance() {
    if (!s_initialized)
        s_sharedInstance = new FTEventManager();
    return s_sharedInstance;
}


FTEventManager::FTEventManager() {
    
}

FTEventManager::~FTEventManager() {
    
}

void FTEventManager::registerDispatcher(const std::shared_ptr<FTEventDispatcherBase>& dispatcher) {
    const std::type_index& type = typeid(*dispatcher);
    FTAssert(event_dispatchers_.find(type) != event_dispatchers_.end(), "FTEvent dispatcher already has registered event dispatcher");
    event_dispatchers_[type] = dispatcher;
}

