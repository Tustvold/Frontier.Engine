#pragma once
#include <Frontier.h>
#include <unordered_map>
#include <vector>
#include <Event/Engine/FTEngineEvents.h>

class FTNode;
class FTAction;

class FTActionManager {
    friend class FTDirector;
public:

    void addAction(FTNode* target, std::unique_ptr<FTAction>&& action);

    void removeActionsForNode(FTNode* target);

    void pauseActionManager() {
        actions_paused_ = true;
    }

    void resumeActionManager() {
        actions_paused_ = false;
    }

private:

    FTActionManager();
    ~FTActionManager();

    void onUpdate(const FTUpdateEvent& event);

    std::unordered_map<FTNode*, std::vector<std::unique_ptr<FTAction>>> actions_;
    std::vector <std::pair<FTNode*, std::unique_ptr<FTAction>>> actions_pending_add_;
    bool actions_paused_;
    bool updating_;
};
