#include "FTIntervalAction.h"
#include <Event/Engine/FTEngineEvents.h>

NS_FT_BEGIN

FTIntervalAction::FTIntervalAction(double time_interval) : time_since_start_(0), time_interval_(time_interval), progress_(0) {
    FTAssert(time_interval >= 0.0, "Cannot create action with negative time interval");
}

FTIntervalAction::~FTIntervalAction() {
}

void FTIntervalAction::onStart(FTNode* node) {
    FTAction::onStart(node);
    time_since_start_ = 0;
    progress_ = 0;
    if (time_interval_ == 0.0f) {
        progress_ = 1.0f;
        setCompleted();
    }
}

void FTIntervalAction::onUpdate(FTNode* node, const FTUpdateEvent& event) {
    time_since_start_ += event.delta_time_;
    progress_ = time_since_start_ / time_interval_;
    if (progress_ >= 1.0f) {
        setCompleted();
        // We cap these at the provided limits - to prevent strange behaviour if a tick is delayed for some reason
        progress_ = 1.0f;
        time_since_start_ = time_interval_;
    }
}

NS_FT_END