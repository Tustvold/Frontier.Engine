#pragma once
#include <Event/Event.h>

NS_FT_BEGIN

struct WindowResizeEvent : public Event {
    WindowResizeEvent(int width, int height) : width_(width), height_(height) {

    }

    int width_;
    int height_;

    bool operator==(const WindowResizeEvent& other) const {
        return width_ == other.width_ && height_ == other.height_;
    }
};

NS_FT_END