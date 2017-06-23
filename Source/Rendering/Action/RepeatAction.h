#pragma once
#include "Action.h"

NS_FT_BEGIN

class RepeatAction : public Action {
public:
    
    // A negative repeat_count will cause the action to repeat forever
    RepeatAction(std::unique_ptr<Action>&& action, int repeat_count);
    virtual ~RepeatAction();

    void onStart(Node* node) override;
    void onUpdate(Node* node, const UpdateEvent& event) override;

protected:
    const int repeat_count_;
    int remaining_count_;
    std::unique_ptr<Action> action_;
};

NS_FT_END