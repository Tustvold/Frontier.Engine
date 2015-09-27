#pragma once
#include <Frontier.h>
#include <Rendering/Mesh/FTVertex.h>

// Base class for all drawable objects
class FTDrawable {
public:
    virtual ~FTDrawable() {
    }

    virtual void draw() = 0;
};
