#pragma once
#include <Frontier.h>
#include "Action.h"
#include <queue>

NS_FT_BEGIN

class ActionSequence : public Action {
public:
    
    ActionSequence();

    virtual ~ActionSequence();

    void addAction(std::unique_ptr<Action>&& action);

    virtual void onStart(Node* node) override;
    virtual void onUpdate(Node* node, const UpdateEvent& event) override;

protected:
    std::vector<std::unique_ptr<Action>> actions_;
    size_t action_index_;
};

NS_FT_END