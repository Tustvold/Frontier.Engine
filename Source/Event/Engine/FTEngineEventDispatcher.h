#pragma once
#include "FTEngineEvents.h"
#include <Event/FTEventDispatcher.h>

class FTEngineEventDispatcher : public FTEventDispatcher<FTUpdateEvent, FTDrawEvent> {
    friend class FTEngine;
public:
    FTEngineEventDispatcher() {

    }

    virtual ~FTEngineEventDispatcher() {

    }
};
