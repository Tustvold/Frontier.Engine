#include <glfwmock.h>
#include <FTEngine.h>
#include <Event/FTEventManager.h>
#include <Event/Keyboard/FTKeyboardEventDispatcher.h>

class MockKeyboardEventListener {
public:
    MOCK_METHOD1(keyPressedEvent, void(const FTKeyPressedEvent&));
    MOCK_METHOD1(keyReleasedEvent, void(const FTKeyReleasedEvent&));
};

TEST(TestKeyboardEventDispatcher, TestKeyPressedEvent) {
    GlfwMock mock;
    FTEngine::setup(true);
    MockKeyboardEventListener listener;

    auto pressed_delegate = Gallant::Delegate1<const FTKeyPressedEvent&>(&listener, &MockKeyboardEventListener::keyPressedEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTKeyboardEventDispatcher>()->registerDelegate(pressed_delegate);

    EXPECT_CALL(listener, keyPressedEvent(FTKeyPressedEvent(GLFW_KEY_1,23,GLFW_MOD_SHIFT)));

    mock.key_callback_(nullptr, GLFW_KEY_1, 23, GLFW_PRESS, GLFW_MOD_SHIFT);

    FTEngine::cleanup();
}


TEST(TestKeyboardEventDispatcher, TestKeyReleasedEvent) {
    GlfwMock mock;
    FTEngine::setup(true);
    MockKeyboardEventListener listener;

    auto released_delegate = Gallant::Delegate1<const FTKeyReleasedEvent&>(&listener, &MockKeyboardEventListener::keyReleasedEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTKeyboardEventDispatcher>()->registerDelegate(released_delegate);

    EXPECT_CALL(listener, keyReleasedEvent(FTKeyReleasedEvent(GLFW_KEY_1, 23, GLFW_MOD_SHIFT)));

    mock.key_callback_(nullptr, GLFW_KEY_1, 23, GLFW_RELEASE, GLFW_MOD_SHIFT);

    FTEngine::cleanup();
}
