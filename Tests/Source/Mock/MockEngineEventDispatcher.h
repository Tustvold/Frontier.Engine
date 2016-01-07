#pragma once
#include <Event/Engine/FTEngineEventDispatcher.h>
#include <FTEngine.h>
#include <Event/FTEventManager.h>

class MockEngineEventDispatcher : public FTEngineEventDispatcher {
public:
    MockEngineEventDispatcher() {

    }

    virtual ~MockEngineEventDispatcher() {

    }

    template <typename T>
    void raiseEvent(const T& event) {
        FTEngineEventDispatcher::raiseEvent<T>(event);
    }
};
