#pragma once
#include <Frontier.h>
#include "FTAction.h"

NS_FT_BEGIN

class FTIntervalAction : public FTAction {
public:
    explicit FTIntervalAction(double time_interval);
    virtual ~FTIntervalAction();

    virtual void onStart(FTNode* node) override;
    virtual void onUpdate(FTNode* node, const FTUpdateEvent& event) override;


protected:
    double time_since_start_;
    const double time_interval_;
    double progress_;
};

using FTDelayAction = FTIntervalAction;

NS_FT_END