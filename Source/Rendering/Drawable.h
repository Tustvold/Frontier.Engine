#pragma once

#include "Frontier.h"

NS_FT_BEGIN

// Base class for all drawable objects
class Drawable {
public:
    virtual ~Drawable() {
    }

    virtual void draw() = 0;
};

NS_FT_END