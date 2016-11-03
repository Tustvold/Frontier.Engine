#pragma once
#include <Frontier.h>
#include "FTAction.h"
#include <queue>

class FTActionSequence : public FTAction {
public:
    
    FTActionSequence();

    virtual ~FTActionSequence();

    void addAction(std::unique_ptr<FTAction>&& action);

    virtual void onStart(FTNode* node) override;
    virtual void onUpdate(FTNode* node, const FTUpdateEvent& event) override;

protected:
    std::vector<std::unique_ptr<FTAction>> actions_;
    size_t action_index_;
};