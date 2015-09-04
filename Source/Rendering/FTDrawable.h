#pragma once

// Base class for all drawable objects
class FTDrawable {
public:
    virtual ~FTDrawable() {
    }

    virtual void draw() = 0;
};
