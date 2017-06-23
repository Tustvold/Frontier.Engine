#pragma once
#include <Frontier.h>
#include <unordered_map>
#include <vector>
#include <Event/Engine/FTEngineEvents.h>

NS_FT_BEGIN

class Node;
class Action;

class ActionManager {
    friend class Director;
public:

    void addAction(Node* target, std::unique_ptr<Action>&& action);

    void removeActionsForNode(Node* target);

    void resetActionsForNode(Node* target);

    void pauseActionManager() {
        actions_paused_ = true;
    }

    void resumeActionManager() {
        actions_paused_ = false;
    }

private:

    ActionManager();
    ~ActionManager();

    void onUpdate(const UpdateEvent& event);

    std::unordered_map<Node*, std::vector<std::unique_ptr<Action>>> actions_;
    std::vector <std::pair<Node*, std::unique_ptr<Action>>> actions_pending_add_;
    bool actions_paused_;
    bool updating_;
};

NS_FT_END
