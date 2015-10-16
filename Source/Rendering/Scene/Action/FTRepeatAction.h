#pragma once
#include "FTAction.h"

class FTRepeatAction : public FTAction {
public:
    
    // A negative repeat_count will cause the action to repeat forever
    FTRepeatAction(std::unique_ptr<FTAction>&& action, int repeat_count);
    virtual ~FTRepeatAction();

    void onStart(FTNode* node) override;
    void onUpdate(FTNode* node, const FTUpdateEvent& event) override;

protected:
    const int repeat_count_;
    int remaining_count_;
    std::unique_ptr<FTAction> action_;
};