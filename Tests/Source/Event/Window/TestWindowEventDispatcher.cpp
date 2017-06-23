#include <glfwmock.h>
#include <Engine.h>
#include <Event/EventManager.h>
#include <Event/Window/WindowEventDispatcher.h>
#include <gmock/gmock.h>

USING_NS_FT

class MockWindowEventListener {
public:
    MOCK_METHOD1(windowResizeEvent, void(const WindowResizeEvent&));
};

TEST(TestWindowEventDispatcher, TestWindowResizeEvent) {
    GlfwMock mock;
    Engine::setup(true, true);
    MockWindowEventListener listener;

    auto resize_delegate = Gallant::Delegate1<const WindowResizeEvent&>(&listener, &MockWindowEventListener::windowResizeEvent);
    Engine::getEventManager()->getEventDispatcher<WindowEventDispatcher>()->registerDelegate(resize_delegate);

    EXPECT_CALL(listener, windowResizeEvent(WindowResizeEvent(1200, 2400)));

    mock.window_size_callback_(nullptr, 1200, 2400);

    Engine::cleanup();
}
