#pragma once
#include <Event/FTEvent.h>

NS_FT_BEGIN

struct FTMouseMoveEvent : public FTEvent {
public:
    FTMouseMoveEvent(const glm::vec2& pos, const glm::vec2& delta) : cursor_pos_(pos), delta_(delta) {

    }

    glm::vec2 cursor_pos_;
    glm::vec2 delta_;

    friend bool operator==(const FTMouseMoveEvent& lhs, const FTMouseMoveEvent& rhs) {
        return lhs.cursor_pos_ == rhs.cursor_pos_ && lhs.delta_ == rhs.delta_;
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

    FTMouseButtonPressedEvent(const glm::vec2& cursor_pos, int mouse_button, bool outside_window)
        : cursor_pos_(cursor_pos), mouse_button_(mouse_button), outside_window_(outside_window) {
    }

    glm::vec2 cursor_pos_;
    int mouse_button_;
    bool outside_window_;


    friend bool operator==(const FTMouseButtonPressedEvent& lhs, const FTMouseButtonPressedEvent& rhs) {
        return lhs.cursor_pos_ == rhs.cursor_pos_
            && lhs.mouse_button_ == rhs.mouse_button_
            && lhs.outside_window_ == rhs.outside_window_;
    }

    friend bool operator!=(const FTMouseButtonPressedEvent& lhs, const FTMouseButtonPressedEvent& rhs) {
        return !(lhs == rhs);
    }
};

struct FTMouseButtonReleasedEvent : public FTEvent {
    FTMouseButtonReleasedEvent(const glm::vec2& cursor_pos, int mouse_button, bool outside_window)
        : cursor_pos_(cursor_pos), mouse_button_(mouse_button), outside_window_(outside_window) {
    }

    glm::vec2 cursor_pos_;
    int mouse_button_;
    bool outside_window_;


    friend bool operator==(const FTMouseButtonReleasedEvent& lhs, const FTMouseButtonReleasedEvent& rhs) {
        return lhs.cursor_pos_ == rhs.cursor_pos_
            && lhs.mouse_button_ == rhs.mouse_button_
            && lhs.outside_window_ == rhs.outside_window_;
    }

    friend bool operator!=(const FTMouseButtonReleasedEvent& lhs, const FTMouseButtonReleasedEvent& rhs) {
        return !(lhs == rhs);
    }
};

struct FTMouseScrollEvent : public FTEvent {


    FTMouseScrollEvent(const glm::vec2& cursor_pos, const glm::vec2& scroll, bool outsize_window)
        : cursor_pos_(cursor_pos),
          scroll_(scroll),
          outsize_window_(outsize_window) {
    }


    friend bool operator==(const FTMouseScrollEvent& lhs, const FTMouseScrollEvent& rhs) {
        return lhs.cursor_pos_ == rhs.cursor_pos_
            && lhs.scroll_ == rhs.scroll_
            && lhs.outsize_window_ == rhs.outsize_window_;
    }

    friend bool operator!=(const FTMouseScrollEvent& lhs, const FTMouseScrollEvent& rhs) {
        return !(lhs == rhs);
    }

    glm::vec2 cursor_pos_;
    glm::vec2 scroll_;

    bool outsize_window_;
};

NS_FT_END