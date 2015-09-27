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

    bool containsPoint(float x, float y) {
        return x_ <= x && x_ + width_ >= x && y_ <= y && y_ + width_ >= y;
    }

    static bool rectIntersectsRect(const FTRect& a, const FTRect& b) {
        return a.x_ < b.x_ + b.width_ && a.x_ + a.width_ > b.x_ && a.y_ < b.y_ + b.height_ && a.y_ + a.height_ > b.y_;
    }
};
