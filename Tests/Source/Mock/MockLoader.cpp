#include "MockLoader.h"
#include <FTEngine.h>
#include <glfwmock.h>

#if __cplusplus < 201402L
// no make_unique support
namespace std {
    template<typename T, typename ...Args>
    std::unique_ptr<T> make_unique( Args&& ...args )
    {
            return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
    }
}
#endif

MockLoader::MockLoader() {
    mock_ = std::make_unique<GlfwMock>();
    FTEngine::init();
    mock_engine_event_dispatcher_ = std::make_shared<MockEngineEventDispatcher>();
    FTEngine::getEventManager()->registerDispatcher(std::static_pointer_cast<FTEngineEventDispatcher>(mock_engine_event_dispatcher_));

    FTEngine::setup(true);
}

MockLoader::~MockLoader() {
    FTEngine::cleanup();
}
