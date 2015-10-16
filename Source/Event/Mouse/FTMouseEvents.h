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

struct FTMouseButtonPressedEvent : public FTEvent {

    FTMouseButtonPressedEvent(double cursor_x, double cursor_y, int mouse_button, bool outside_window)
        : cursor_x_(cursor_x), cursor_y_(cursor_y), mouse_button_(mouse_button), outside_window_(outside_window) {
    }

    double cursor_x_;
    double cursor_y_;
    int mouse_button_;
    bool outside_window_;

    bool operator==(const FTMouseButtonPressedEvent& other) const {
        return cursor_x_ == other.cursor_x_ && cursor_y_ == other.cursor_y_ && mouse_button_ == other.mouse_button_ && outside_window_ == other.outside_window_;
    }
};

struct FTMouseButtonReleasedEvent : public FTEvent {
    FTMouseButtonReleasedEvent(double cursor_x, double cursor_y, int mouse_button, bool outside_window)
        : cursor_x_(cursor_x), cursor_y_(cursor_y), mouse_button_(mouse_button), outside_window_(outside_window) {
    }

    double cursor_x_;
    double cursor_y_;
    int mouse_button_;
    bool outside_window_;

    bool operator==(const FTMouseButtonReleasedEvent& other) const {
        return cursor_x_ == other.cursor_x_ && cursor_y_ == other.cursor_y_ && mouse_button_ == other.mouse_button_ && outside_window_ == other.outside_window_;
    }
};
