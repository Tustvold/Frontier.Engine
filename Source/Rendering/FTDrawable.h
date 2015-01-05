#pragma once
#include <FTObject.h>

// Base class for all drawable objects
class FTDrawable : public FTObject {
public:
	virtual void draw() = 0;
};
