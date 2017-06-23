#include "MockLoader.h"
#include <Engine.h>
#include <glfwmock.h>

NS_FT_BEGIN

MockLoader::MockLoader() {
    mock_ = std::make_unique<GlfwMock>();
    Engine::init();
    mock_engine_event_dispatcher_ = std::make_shared<MockEngineEventDispatcher>();
    Engine::getEventManager()->registerDispatcher(std::static_pointer_cast<EngineEventDispatcher>(mock_engine_event_dispatcher_));

    Engine::setup(true, true);
}

MockLoader::~MockLoader() {
    Engine::cleanup();
}

NS_FT_END