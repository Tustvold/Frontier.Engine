#pragma once
#include <memory>
#include <gmock/gmock.h>
#include <Mock/MockEngineEventDispatcher.h>

class GlfwMock;

// Sets up GlfwMock and FTEngine in its constructor
// and cleans them up in its destructor
// This largely exists to speed up compilation by preventing
// test files having to include GlfwMock unless they really need to
class MockLoader {
public:
    MockLoader();

    ~MockLoader();

    MockEngineEventDispatcher* getMockEngineEventDispatcher() {
        return mock_engine_event_dispatcher_.get();
    }

private:
    std::unique_ptr<GlfwMock> mock_;
    std::shared_ptr<MockEngineEventDispatcher> mock_engine_event_dispatcher_;
};
