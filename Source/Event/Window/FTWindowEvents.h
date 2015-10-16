#pragma once
#include <Event/FTEvent.h>

struct FTWindowResizeEvent : public FTEvent {
    FTWindowResizeEvent(int width, int height) : width_(width), height_(height) {

    }

    int width_;
    int height_;

    bool operator==(const FTWindowResizeEvent& other) const {
        return width_ == other.width_ && height_ == other.height_;
    }
};
