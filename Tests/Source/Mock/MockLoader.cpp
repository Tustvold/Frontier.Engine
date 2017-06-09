#include "MockLoader.h"
#include <FTEngine.h>
#include <glfwmock.h>

MockLoader::MockLoader() {
    mock_ = std::make_unique<GlfwMock>();
    FTEngine::init();
    mock_engine_event_dispatcher_ = std::make_shared<MockEngineEventDispatcher>();
    FTEngine::getEventManager()->registerDispatcher(std::static_pointer_cast<FTEngineEventDispatcher>(mock_engine_event_dispatcher_));

    FTEngine::setup(true, true);
}

MockLoader::~MockLoader() {
    FTEngine::cleanup();
}
