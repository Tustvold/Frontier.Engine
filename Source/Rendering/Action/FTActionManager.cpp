#include "FTActionManager.h"
#include "FTAction.h"
#include <FTEngine.h>
#include <Event/FTEventManager.h>
#include <Event/Engine/FTEngineEventDispatcher.h>
#include <algorithm>
#include <Rendering/FTNode.h>

void FTActionManager::addAction(FTNode* target, std::unique_ptr<FTAction>&& action) {
    if (!updating_) {
        action->onStart(target);
        actions_[target].push_back(std::move(action));
    } else {
        actions_pending_add_.push_back(std::make_pair(target, std::move(action)));
    }
    
}

void FTActionManager::removeActionsForNode(FTNode* target) {
    actions_.erase(target);
}

FTActionManager::FTActionManager() : actions_paused_(false) {
    FTEngine::getEventManager()->registerDelegate<FTEngineEventDispatcher>(this, &FTActionManager::onUpdate);
}

FTActionManager::~FTActionManager() {
    FTEngine::getEventManager()->unregisterDelegate<FTEngineEventDispatcher>(this, &FTActionManager::onUpdate);
}

void FTActionManager::onUpdate(const FTUpdateEvent& event) {
    updating_ = true;
    // If an action is paused it will only be removed once it has been resumed
    for (auto store_iterator = actions_.begin(); store_iterator != actions_.end(); ++store_iterator) {
        
        auto node = store_iterator->first;
        if (node->getActionsPaused() || !node->getIsActive())
            continue;
        auto& store = store_iterator->second;
        
        store.erase(std::remove_if(store.begin(), store.end(),
            [event, node](std::unique_ptr<FTAction>& action)
        {
            
            if (action->getIsPaused()) {
                return false;
            }
            if (!action->getCompleted())
                action->onUpdate(node, event);
            return action->getCompleted();
        }), store.end());
    }

    updating_ = false;
    for (auto it = actions_pending_add_.begin(); it != actions_pending_add_.end(); ++it) {
        addAction(it->first, std::move(it->second));
    }
    actions_pending_add_.clear();
}
