#pragma once
#include <Frontier.h>
#include "Action.h"

NS_FT_BEGIN

class IntervalAction : public Action {
public:
    explicit IntervalAction(double time_interval);
    virtual ~IntervalAction();

    virtual void onStart(Node* node) override;
    virtual void onUpdate(Node* node, const UpdateEvent& event) override;


protected:
    double time_since_start_;
    const double time_interval_;
    double progress_;
};

using DelayAction = IntervalAction;

NS_FT_END