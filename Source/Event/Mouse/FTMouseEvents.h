#pragma once
#include <Event/FTEvent.h>

struct FTMouseMoveEvent : public FTEvent {
public:
    FTMouseMoveEvent(double x, double y, double delta_x, double delta_y) : x_(x), y_(y), delta_x_(delta_x), delta_y_(delta_y) {
        
    }

    double x_;
    double y_;
    double delta_x_;
    double delta_y_;

    bool operator==(const FTMouseMoveEvent& other) const {
        return x_ == other.x_ && y_ == other.y_ && delta_x_ == other.delta_x_ && delta_y_ == other.delta_y_;
    }
};

struct FTMouseEnterEvent : public FTEvent {
    
};

struct FTMouseExitEvent : public FTEvent {
    
};