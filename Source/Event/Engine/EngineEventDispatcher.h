#pragma once

#include "FTEngineEvents.h"
#include <Event/EventDispatcher.h>

NS_FT_BEGIN

class EngineEventDispatcher : public EventDispatcher<UpdateEvent, DrawEvent, PreTickEvent> {
    friend class Engine;

public:
    EngineEventDispatcher() {

    }

    virtual ~EngineEventDispatcher() {

    }
};

NS_FT_END