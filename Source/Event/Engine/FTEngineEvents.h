#pragma once
#include <Frontier.h>
#include <Event/Event.h>

NS_FT_BEGIN

struct UpdateEvent : public Event {
    UpdateEvent() : delta_time_(0) {

    }

    explicit UpdateEvent(double delta_time) : delta_time_(delta_time) {

    }

    double delta_time_;

    bool operator ==(const UpdateEvent& other) const {
        return delta_time_ == other.delta_time_;
    }
};


struct DrawEvent : public Event {
    DrawEvent() : delta_time_(0), average_fps_(0), window_(nullptr) {

    }

    double delta_time_;
    double average_fps_;
    GLFWwindow* window_;

    bool operator ==(const DrawEvent& other) const {
        return delta_time_ == other.delta_time_ && average_fps_ == other.average_fps_ && window_ == other.window_;
    }
};

// Used internally for tasks such as switching scenes
struct PreTickEvent : public Event {
    
};

NS_FT_END