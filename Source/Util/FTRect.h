#pragma once

template <typename T>
struct FTRect {
    T x_;
    T y_;
    T width_;
    T height_;

    FTRect() : x_(0),y_(0),width_(0),height_(0) {

    }

    FTRect(T x, T y, T width, T height) {
        x_ = x;
        y_ = y;
        width_ = width;
        height_ = height;
    }
};
