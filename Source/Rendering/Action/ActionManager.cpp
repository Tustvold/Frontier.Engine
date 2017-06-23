#include "ActionManager.h"
#include "Action.h"
#include <Engine.h>
#include <Event/EventManager.h>
#include <Event/Engine/EngineEventDispatcher.h>
#include <algorithm>
#include <Rendering/Node.h>

NS_FT_BEGIN

void ActionManager::addAction(Node* target, std::unique_ptr<Action>&& action) {
    if (!updating_) {
        action->onStart(target);
        actions_[target].push_back(std::move(action));
    } else {
        actions_pending_add_.push_back(std::make_pair(target, std::move(action)));
    }
    
}

void ActionManager::removeActionsForNode(Node* target) {
    FTAssert(!updating_, "Cannot remove actions whilst updating");
    actions_.erase(target);
}

void ActionManager::resetActionsForNode(Node* target) {
    FTAssert(!updating_, "Cannot reset actions whilst updating");
    auto& actions = actions_[target];
    for (auto it = actions.begin(); it != actions.end(); it++) {
        (*it)->onStart(target);
    }
}

ActionManager::ActionManager() : actions_paused_(false), updating_(false) {
    Engine::getEventManager()->registerDelegate<EngineEventDispatcher>(this, &ActionManager::onUpdate);
}

ActionManager::~ActionManager() {
    Engine::getEventManager()->unregisterDelegate<EngineEventDispatcher>(this, &ActionManager::onUpdate);
}

void ActionManager::onUpdate(const UpdateEvent& event) {
    updating_ = true;
    // If an action is paused it will only be removed once it has been resumed
    for (auto store_iterator = actions_.begin(); store_iterator != actions_.end(); ++store_iterator) {
        
        auto node = store_iterator->first;
        if (node->getActionsPaused() || !node->getIsActive())
            continue;
        auto& store = store_iterator->second;
        
        store.erase(std::remove_if(store.begin(), store.end(),
            [event, node](std::unique_ptr<Action>& action)
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

NS_FT_END