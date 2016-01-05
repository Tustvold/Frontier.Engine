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

    friend bool operator==(const FTMouseMoveEvent& lhs, const FTMouseMoveEvent& rhs) {
        return lhs.x_ == rhs.x_
            && lhs.y_ == rhs.y_
            && lhs.delta_x_ == rhs.delta_x_
            && lhs.delta_y_ == rhs.delta_y_;
    }

    friend bool operator!=(const FTMouseMoveEvent& lhs, const FTMouseMoveEvent& rhs) {
        return !(lhs == rhs);
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


    friend bool operator==(const FTMouseButtonPressedEvent& lhs, const FTMouseButtonPressedEvent& rhs) {
        return lhs.cursor_x_ == rhs.cursor_x_
            && lhs.cursor_y_ == rhs.cursor_y_
            && lhs.mouse_button_ == rhs.mouse_button_
            && lhs.outside_window_ == rhs.outside_window_;
    }

    friend bool operator!=(const FTMouseButtonPressedEvent& lhs, const FTMouseButtonPressedEvent& rhs) {
        return !(lhs == rhs);
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


    friend bool operator==(const FTMouseButtonReleasedEvent& lhs, const FTMouseButtonReleasedEvent& rhs) {
        return lhs.cursor_x_ == rhs.cursor_x_
            && lhs.cursor_y_ == rhs.cursor_y_
            && lhs.mouse_button_ == rhs.mouse_button_
            && lhs.outside_window_ == rhs.outside_window_;
    }

    friend bool operator!=(const FTMouseButtonReleasedEvent& lhs, const FTMouseButtonReleasedEvent& rhs) {
        return !(lhs == rhs);
    }
};

struct FTMouseScrollEvent : public FTEvent {


    FTMouseScrollEvent(double cursor_x, double cursor_y, double scroll_x, double scroll_y, bool outsize_window)
        : cursor_x_(cursor_x),
          cursor_y_(cursor_y),
          scroll_x_(scroll_x),
          scroll_y_(scroll_y),
          outsize_window_(outsize_window) {
    }


    friend bool operator==(const FTMouseScrollEvent& lhs, const FTMouseScrollEvent& rhs) {
        return lhs.cursor_x_ == rhs.cursor_x_
            && lhs.cursor_y_ == rhs.cursor_y_
            && lhs.scroll_x_ == rhs.scroll_x_
            && lhs.scroll_y_ == rhs.scroll_y_
            && lhs.outsize_window_ == rhs.outsize_window_;
    }

    friend bool operator!=(const FTMouseScrollEvent& lhs, const FTMouseScrollEvent& rhs) {
        return !(lhs == rhs);
    }

    double cursor_x_;
    double cursor_y_;
    double scroll_x_;
    double scroll_y_;
    bool outsize_window_;
};