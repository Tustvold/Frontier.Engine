#pragma once
#include <Event/FTEvent.h>

struct FTPreDrawEvent : public FTEvent {
    FTPreDrawEvent() : delta_time_(0), average_fps_(0) {
        
    }

    FTPreDrawEvent(double delta_time, double average_fps) : delta_time_(delta_time), average_fps_(average_fps) {
        
    }

    double delta_time_;
    double average_fps_;
};