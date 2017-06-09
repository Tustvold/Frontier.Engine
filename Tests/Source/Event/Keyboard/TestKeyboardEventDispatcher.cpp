#include <glfwmock.h>
#include <FTEngine.h>
#include <Event/Keyboard/FTKeyboardEventDispatcher.h>
#include <Event/FTEventManager.h>
#include <gmock/gmock.h>

class MockKeyboardEventListener {
public:
    MOCK_METHOD1(keyPressedEvent, void(const FTKeyPressedEvent&));
    MOCK_METHOD1(keyRepeatEvent, void(const FTKeyRepeatEvent&));
    MOCK_METHOD1(keyReleasedEvent, void(const FTKeyReleasedEvent&));
    MOCK_METHOD1(charEvent, void(const FTCharInputEvent&));
};

TEST(TestKeyboardEventDispatcher, TestKeyPressedEvent) {
    GlfwMock mock;
    FTEngine::setup(true, true);
    MockKeyboardEventListener listener;

    auto pressed_delegate = Gallant::Delegate1<const FTKeyPressedEvent&>(&listener, &MockKeyboardEventListener::keyPressedEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTKeyboardEventDispatcher>()->registerDelegate(pressed_delegate);

    EXPECT_CALL(listener, keyPressedEvent(FTKeyPressedEvent(GLFW_KEY_1,23,GLFW_MOD_SHIFT)));

    mock.key_callback_(nullptr, GLFW_KEY_1, 23, GLFW_PRESS, GLFW_MOD_SHIFT);

    FTEngine::cleanup();
}

TEST(TestKeyboardEventDispatcher, TestKeyRepeatEvent) {
    GlfwMock mock;
    FTEngine::setup(true, true);
    MockKeyboardEventListener listener;

    FTEngine::getEventManager()->registerDelegate<FTKeyboardEventDispatcher>(&listener, &MockKeyboardEventListener::keyRepeatEvent);

    EXPECT_CALL(listener, keyRepeatEvent(FTKeyRepeatEvent(GLFW_KEY_1, 23, GLFW_MOD_SHIFT)));

    mock.key_callback_(nullptr, GLFW_KEY_1, 23, GLFW_REPEAT, GLFW_MOD_SHIFT);

    FTEngine::cleanup();
}
TEST(TestKeyboardEventDispatcher, TestKeyReleasedEvent) {
    GlfwMock mock;
    FTEngine::setup(true, true);
    MockKeyboardEventListener listener;

    auto released_delegate = Gallant::Delegate1<const FTKeyReleasedEvent&>(&listener, &MockKeyboardEventListener::keyReleasedEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTKeyboardEventDispatcher>()->registerDelegate(released_delegate);

    EXPECT_CALL(listener, keyReleasedEvent(FTKeyReleasedEvent(GLFW_KEY_1, 23, GLFW_MOD_SHIFT)));

    mock.key_callback_(nullptr, GLFW_KEY_1, 23, GLFW_RELEASE, GLFW_MOD_SHIFT);

    FTEngine::cleanup();
}

TEST(TestKeyboardEventDispatcher, TestCharInputEvent) {
    GlfwMock mock;
    FTEngine::setup(true, true);
    MockKeyboardEventListener listener;

    FTEngine::getEventManager()->registerDelegate<FTKeyboardEventDispatcher>(&listener, &MockKeyboardEventListener::charEvent);

    EXPECT_CALL(listener, charEvent(FTCharInputEvent(1243,GLFW_MOD_ALT)));

    mock.char_mods_callback_(nullptr, 1243, GLFW_MOD_ALT);

    FTEngine::cleanup();
}
