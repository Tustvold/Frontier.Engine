#pragma once

#include "FTEngineEvents.h"
#include <Event/FTEventDispatcher.h>

NS_FT_BEGIN

class FTEngineEventDispatcher : public FTEventDispatcher<FTUpdateEvent, FTDrawEvent, FTPreTickEvent> {
    friend class FTEngine;

public:
    FTEngineEventDispatcher() {

    }

    virtual ~FTEngineEventDispatcher() {

    }
};

NS_FT_END