#include <glfwmock.h>
#include <FTEngine.h>
#include <Event/FTEventManager.h>
#include <Event/Window/FTWindowEventDispatcher.h>
#include <gmock/gmock.h>

class MockWindowEventListener {
public:
    MOCK_METHOD1(windowResizeEvent, void(const FTWindowResizeEvent&));
};

TEST(TestWindowEventDispatcher, TestWindowResizeEvent) {
    GlfwMock mock;
    FTEngine::setup(true, true);
    MockWindowEventListener listener;

    auto resize_delegate = Gallant::Delegate1<const FTWindowResizeEvent&>(&listener, &MockWindowEventListener::windowResizeEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTWindowEventDispatcher>()->registerDelegate(resize_delegate);

    EXPECT_CALL(listener, windowResizeEvent(FTWindowResizeEvent(1200, 2400)));

    mock.window_size_callback_(nullptr, 1200, 2400);

    FTEngine::cleanup();
}
