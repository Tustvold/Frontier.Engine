#include <Event/Engine/FTEngineEventDispatcher.h>
#include <FTEngine.h>
#include <Event/FTEventManager.h>

class MockEngineEventDispatcher : public FTEngineEventDispatcher {
public:
    MockEngineEventDispatcher() {
        
    }

    virtual ~MockEngineEventDispatcher() {
        
    }

    void raiseEvent(const FTPreDrawEvent& event) {
        FTEngineEventDispatcher::raiseEvent(event);
    }
};