#include <glfwmock.h>
#include <Engine.h>
#include <Event/Keyboard/KeyboardEventDispatcher.h>
#include <Event/EventManager.h>
#include <gmock/gmock.h>

USING_NS_FT

class MockKeyboardEventListener {
public:
    MOCK_METHOD1(keyPressedEvent, void(const KeyPressedEvent&));
    MOCK_METHOD1(keyRepeatEvent, void(const KeyRepeatEvent&));
    MOCK_METHOD1(keyReleasedEvent, void(const KeyReleasedEvent&));
    MOCK_METHOD1(charEvent, void(const CharInputEvent&));
};

TEST(TestKeyboardEventDispatcher, TestKeyPressedEvent) {
    GlfwMock mock;
    Engine::setup(true, true);
    MockKeyboardEventListener listener;

    auto pressed_delegate = Gallant::Delegate1<const KeyPressedEvent&>(&listener, &MockKeyboardEventListener::keyPressedEvent);
    Engine::getEventManager()->getEventDispatcher<KeyboardEventDispatcher>()->registerDelegate(pressed_delegate);

    EXPECT_CALL(listener, keyPressedEvent(KeyPressedEvent(GLFW_KEY_1,23,GLFW_MOD_SHIFT)));

    mock.key_callback_(nullptr, GLFW_KEY_1, 23, GLFW_PRESS, GLFW_MOD_SHIFT);

    Engine::cleanup();
}

TEST(TestKeyboardEventDispatcher, TestKeyRepeatEvent) {
    GlfwMock mock;
    Engine::setup(true, true);
    MockKeyboardEventListener listener;

    Engine::getEventManager()->registerDelegate<KeyboardEventDispatcher>(&listener, &MockKeyboardEventListener::keyRepeatEvent);

    EXPECT_CALL(listener, keyRepeatEvent(KeyRepeatEvent(GLFW_KEY_1, 23, GLFW_MOD_SHIFT)));

    mock.key_callback_(nullptr, GLFW_KEY_1, 23, GLFW_REPEAT, GLFW_MOD_SHIFT);

    Engine::cleanup();
}
TEST(TestKeyboardEventDispatcher, TestKeyReleasedEvent) {
    GlfwMock mock;
    Engine::setup(true, true);
    MockKeyboardEventListener listener;

    auto released_delegate = Gallant::Delegate1<const KeyReleasedEvent&>(&listener, &MockKeyboardEventListener::keyReleasedEvent);
    Engine::getEventManager()->getEventDispatcher<KeyboardEventDispatcher>()->registerDelegate(released_delegate);

    EXPECT_CALL(listener, keyReleasedEvent(KeyReleasedEvent(GLFW_KEY_1, 23, GLFW_MOD_SHIFT)));

    mock.key_callback_(nullptr, GLFW_KEY_1, 23, GLFW_RELEASE, GLFW_MOD_SHIFT);

    Engine::cleanup();
}

TEST(TestKeyboardEventDispatcher, TestCharInputEvent) {
    GlfwMock mock;
    Engine::setup(true, true);
    MockKeyboardEventListener listener;

    Engine::getEventManager()->registerDelegate<KeyboardEventDispatcher>(&listener, &MockKeyboardEventListener::charEvent);

    EXPECT_CALL(listener, charEvent(CharInputEvent(1243,GLFW_MOD_ALT)));

    mock.char_mods_callback_(nullptr, 1243, GLFW_MOD_ALT);

    Engine::cleanup();
}
