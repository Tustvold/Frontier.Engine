#pragma once
#include <Event/Engine/EngineEventDispatcher.h>
#include <Engine.h>
#include <Event/EventManager.h>

NS_FT_BEGIN

class MockEngineEventDispatcher : public EngineEventDispatcher {
public:
    MockEngineEventDispatcher() {

    }

    virtual ~MockEngineEventDispatcher() {

    }

    template <typename T>
    void raiseEvent(const T& event) {
        EngineEventDispatcher::raiseEvent<T>(event);
    }
};

NS_FT_END
