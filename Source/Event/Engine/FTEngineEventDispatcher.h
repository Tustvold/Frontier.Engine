#pragma once
#include "FTEngineEvents.h"
#include <Event/FTEventDispatcher.h>

class FTEngineEventDispatcher : public FTEventDispatcher<FTPreDrawEvent> {
    friend class FTDirector;
public:
    FTEngineEventDispatcher() {
        
    }

    virtual ~FTEngineEventDispatcher() {
        
    }
};