#pragma once

#include "Frontier.h"

NS_FT_BEGIN

template <typename T>
struct Rect {
    T x_;
    T y_;
    T width_;
    T height_;

    Rect() : x_(0),y_(0),width_(0),height_(0) {

    }

    Rect(T x, T y, T width, T height) {
        x_ = x;
        y_ = y;
        width_ = width;
        height_ = height;
    }

    bool containsPoint(float x, float y) {
        return x_ <= x && x_ + width_ >= x && y_ <= y && y_ + width_ >= y;
    }

    static bool rectIntersectsRect(const Rect& a, const Rect& b) {
        return a.x_ < b.x_ + b.width_ && a.x_ + a.width_ > b.x_ && a.y_ < b.y_ + b.height_ && a.y_ + a.height_ > b.y_;
    }
};

NS_FT_END