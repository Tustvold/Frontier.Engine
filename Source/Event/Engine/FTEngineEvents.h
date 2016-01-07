#pragma once
#include <Frontier.h>
#include <Event/FTEvent.h>

struct FTUpdateEvent : public FTEvent {
    FTUpdateEvent() : delta_time_(0) {

    }

    explicit FTUpdateEvent(double delta_time) : delta_time_(delta_time) {

    }

    double delta_time_;

    bool operator ==(const FTUpdateEvent& other) const {
        return delta_time_ == other.delta_time_;
    }
};


struct FTDrawEvent : public FTEvent {
    FTDrawEvent() : delta_time_(0), average_fps_(0), window_(nullptr) {

    }

    double delta_time_;
    double average_fps_;
    GLFWwindow* window_;

    bool operator ==(const FTDrawEvent& other) const {
        return delta_time_ == other.delta_time_ && average_fps_ == other.average_fps_ && window_ == other.window_;
    }
};

// Used internally for tasks such as switching scenes
struct FTPreTickEvent : public FTEvent {
    
};