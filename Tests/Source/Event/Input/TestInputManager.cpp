#include <glfwmock.h>
#include <Engine.h>
#include <Event/Input/InputManager.h>
#include <Mock/MockEngineEventDispatcher.h>
#include <gmock/gmock.h>

USING_NS_FT

class MockMouseDelegate : public MouseDelegate {
public:
    bool getMouseDelegateEnabled() const override {
        return true;
    }

    MOCK_METHOD1(onMouseDown, bool(const MouseButtonPressedEvent&));
    MOCK_METHOD2(onMouseDrag, void(const MouseMoveEvent&, int));
    MOCK_METHOD1(onMouseRelease, void(const MouseButtonReleasedEvent&));

    MockMouseDelegate(int priority) {
        setMouseDelegatePriority(priority);
    }
};

class MockKeyboardDelegate : public KeyboardDelegate {
public:

    MockKeyboardDelegate(int priority) {
        setKeyboardDelegatePriority(priority);
    }

    bool getKeyboardDelegateEnabled() const override {
        return true;
    }


    MOCK_METHOD1(onKeyPressed, bool(const KeyPressedEvent& event));
    MOCK_METHOD1(onKeyRepeat, void(const KeyRepeatEvent& event));
    MOCK_METHOD1(onKeyRelease, void(const KeyReleasedEvent& event));
};

TEST(TestInputManager, TestKeyStatePressed) {
    GlfwMock mock;
    Engine::setup(true, true);

    auto state = Engine::getInputManager()->getKeyState("Forward", GLFW_KEY_0);

    EXPECT_FALSE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_0, 23, GLFW_PRESS, 0);

    EXPECT_TRUE(state->isPressed());

    Engine::cleanup();
}

TEST(TestInputManager, TestKeyStateReleased) {
    GlfwMock mock;
    Engine::init();
    auto engine_event_dispatcher = std::make_shared<MockEngineEventDispatcher>();
    Engine::getEventManager()->registerDispatcher(std::static_pointer_cast<EngineEventDispatcher>(engine_event_dispatcher));
    Engine::setup(true, true);

    auto state = Engine::getInputManager()->getKeyState("Forward", GLFW_KEY_0);

    EXPECT_FALSE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_0, 23, GLFW_PRESS, 0);

    EXPECT_TRUE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_0, 23, GLFW_RELEASE, 0);

    EXPECT_FALSE(state->isPressed());

    Engine::cleanup();
}

TEST(TestInputManager, TestKeyStateMultiMap) {
    GlfwMock mock;
    Engine::init();
    auto engine_event_dispatcher = std::make_shared<MockEngineEventDispatcher>();
    Engine::getEventManager()->registerDispatcher(std::static_pointer_cast<EngineEventDispatcher>(engine_event_dispatcher));
    Engine::setup(true, true);

    auto state = Engine::getInputManager()->getKeyState("Forward", GLFW_KEY_0);
    state->addMapping(GLFW_KEY_1, 0);

    EXPECT_FALSE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_0, 23, GLFW_PRESS, 0);

    EXPECT_TRUE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_0, 23, GLFW_RELEASE, 0);


    EXPECT_FALSE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_1, 23, GLFW_PRESS, 0);

    EXPECT_TRUE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_1, 23, GLFW_RELEASE, 0);

    EXPECT_FALSE(state->isPressed());

    Engine::cleanup();
}


TEST(TestInputManager, TestKeyStateMultiMap2) {
    GlfwMock mock;
    Engine::init();
    auto engine_event_dispatcher = std::make_shared<MockEngineEventDispatcher>();
    Engine::getEventManager()->registerDispatcher(std::static_pointer_cast<EngineEventDispatcher>(engine_event_dispatcher));
    Engine::setup(true, true);

    auto state = Engine::getInputManager()->getKeyState("Forward", GLFW_KEY_0);
    state->addMapping(GLFW_KEY_1, 0);

    EXPECT_FALSE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_1, 23, GLFW_PRESS, 0);
    EXPECT_TRUE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_0, 23, GLFW_PRESS, 0);

    EXPECT_TRUE(state->isPressed());
    
    mock.key_callback_(nullptr, GLFW_KEY_0, 23, GLFW_RELEASE, 0);

    EXPECT_TRUE(state->isPressed());
    mock.key_callback_(nullptr, GLFW_KEY_1, 23, GLFW_RELEASE, 0);

    EXPECT_FALSE(state->isPressed());

    Engine::cleanup();
}

TEST(TestInputManager, TestKeyStateMods) {
    GlfwMock mock;
    Engine::init();
    auto engine_event_dispatcher = std::make_shared<MockEngineEventDispatcher>();
    Engine::getEventManager()->registerDispatcher(std::static_pointer_cast<EngineEventDispatcher>(engine_event_dispatcher));
    Engine::setup(true, true);

    auto state = Engine::getInputManager()->getKeyState("Forward", GLFW_KEY_0, GLFW_MOD_ALT | GLFW_MOD_CONTROL);

    EXPECT_FALSE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_0, 0, GLFW_PRESS, 0);

    EXPECT_FALSE(state->isPressed());
    mock.key_callback_(nullptr, GLFW_KEY_0, 0, GLFW_RELEASE, 0);

    EXPECT_FALSE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_0, 23, GLFW_PRESS, GLFW_MOD_ALT | GLFW_MOD_CONTROL | GLFW_MOD_SHIFT);

    EXPECT_TRUE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_0, 23, GLFW_RELEASE, 0);

    EXPECT_FALSE(state->isPressed());

    Engine::cleanup();
}

TEST(TestInputManager, TestMouseDown) {
    GlfwMock mock;
    Engine::setup(true, true);

    MockMouseDelegate del1(5);
    MockMouseDelegate del2(8);
    MockMouseDelegate del3(7);

    EXPECT_CALL(del1, onMouseDown(testing::_)).Times(0);

    EXPECT_CALL(del2, onMouseDown(MouseButtonPressedEvent(glm::vec2(-1), GLFW_MOUSE_BUTTON_LEFT, true)))
                                                                                                   .WillOnce(testing::Return(true));

    EXPECT_CALL(del3, onMouseDown(testing::_)).Times(0);


    Engine::getInputManager()->addMouseDelegate(&del1);
    Engine::getInputManager()->addMouseDelegate(&del2);
    Engine::getInputManager()->addMouseDelegate(&del3);

    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);


    Engine::cleanup();
}

TEST(TestInputManager, TestMouseDownChained) {
    GlfwMock mock;
    Engine::setup(true, true);

    MockMouseDelegate del1(5);
    MockMouseDelegate del2(8);
    MockMouseDelegate del3(7);

    testing::Sequence s;

    EXPECT_CALL(del1, onMouseDown(testing::_)).Times(0);

    EXPECT_CALL(del2, onMouseDown(MouseButtonPressedEvent(glm::vec2(-1), GLFW_MOUSE_BUTTON_LEFT, true))).InSequence(s)
                                                                                                   .WillOnce(testing::Return(false));

    EXPECT_CALL(del3, onMouseDown(MouseButtonPressedEvent(glm::vec2(-1), GLFW_MOUSE_BUTTON_LEFT, true))).InSequence(s)
                                                                                                   .WillOnce(testing::Return(true));


    Engine::getInputManager()->addMouseDelegate(&del1);
    Engine::getInputManager()->addMouseDelegate(&del2);
    Engine::getInputManager()->addMouseDelegate(&del3);

    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);


    Engine::cleanup();
}

TEST(TestInputManager, TestMouseExit) {
    GlfwMock mock;
    Engine::setup(true, true);

    MockMouseDelegate del1(5);
    MockMouseDelegate del2(8);
    MockMouseDelegate del3(7);

    testing::Sequence s;

    EXPECT_CALL(del1, onMouseDown(testing::_)).Times(0);

    EXPECT_CALL(del2, onMouseDown(MouseButtonPressedEvent(glm::vec2(240, 80), GLFW_MOUSE_BUTTON_LEFT, false)))
                                                                                                     .InSequence(s)
                                                                                                     .WillOnce(testing::Return(false));

    EXPECT_CALL(del3, onMouseDown(MouseButtonPressedEvent(glm::vec2(240, 80), GLFW_MOUSE_BUTTON_LEFT, false)))
                                                                                                     .InSequence(s)
                                                                                                     .WillOnce(testing::Return(true));

    EXPECT_CALL(del1, onMouseDrag(testing::_, testing::_)).Times(0);

    EXPECT_CALL(del2, onMouseDrag(testing::_, testing::_)).Times(0);

    EXPECT_CALL(del3, onMouseDrag(testing::_, GLFW_MOUSE_BUTTON_LEFT)).Times(1).InSequence(s);

    EXPECT_CALL(del1, onMouseRelease(testing::_)).Times(0);

    EXPECT_CALL(del2, onMouseRelease(testing::_)).Times(0);

    EXPECT_CALL(del3, onMouseRelease(testing::_)).Times(1).InSequence(s);


    Engine::getInputManager()->addMouseDelegate(&del1);
    Engine::getInputManager()->addMouseDelegate(&del2);
    Engine::getInputManager()->addMouseDelegate(&del3);

    auto screensize = Engine::getWindowSize();

    mock.mouse_pos_callback_(nullptr, 240, screensize.y - 80);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
    mock.mouse_pos_callback_(nullptr, 480, screensize.y - 60);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);
    mock.mouse_pos_callback_(nullptr, 530, screensize.y - 60);


    Engine::cleanup();
}

TEST(TestInputManager, TestMultipleMouseButtons) {
    GlfwMock mock;
    Engine::setup(true, true);

    MockMouseDelegate del(5);

    testing::Sequence s;


    EXPECT_CALL(del, onMouseDown(MouseButtonPressedEvent(glm::vec2(240, 80), GLFW_MOUSE_BUTTON_LEFT, false)))
                                                                                                    .InSequence(s)
                                                                                                    .WillOnce(testing::Return(true));

    EXPECT_CALL(del, onMouseDown(MouseButtonPressedEvent(glm::vec2(240, 80), GLFW_MOUSE_BUTTON_RIGHT, false)))
                                                                                                     .InSequence(s)
                                                                                                     .WillOnce(testing::Return(true));



    EXPECT_CALL(del, onMouseDrag(testing::_, GLFW_MOUSE_BUTTON_LEFT))
                                                                     .Times(1)
                                                                     .InSequence(s);


    EXPECT_CALL(del, onMouseDrag(testing::_, GLFW_MOUSE_BUTTON_RIGHT))
                                                                      .Times(1)
                                                                      .InSequence(s);

    EXPECT_CALL(del, onMouseRelease(MouseButtonReleasedEvent(glm::vec2(480, 60), GLFW_MOUSE_BUTTON_RIGHT, false)))
                                                                                                         .Times(1)
                                                                                                         .InSequence(s);

    EXPECT_CALL(del, onMouseRelease(MouseButtonReleasedEvent(glm::vec2(480, 60), GLFW_MOUSE_BUTTON_LEFT, false)))
                                                                                                        .Times(1)
                                                                                                        .InSequence(s);



    Engine::getInputManager()->addMouseDelegate(&del);

    auto screensize = Engine::getWindowSize();

    mock.mouse_pos_callback_(nullptr, 240, screensize.y - 80);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS, 0);
    mock.mouse_pos_callback_(nullptr, 480, screensize.y - 60);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_RIGHT, GLFW_RELEASE, 0);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);
    mock.mouse_pos_callback_(nullptr, 530, screensize.y - 60);


    Engine::cleanup();
}

TEST(TestInputManager, TestMouseDelegateExit) {
    GlfwMock mock;
    Engine::setup(true, true);

    MockMouseDelegate del(5);

    testing::InSequence s;


    EXPECT_CALL(del, onMouseDown(MouseButtonPressedEvent(glm::vec2(500, 200), GLFW_MOUSE_BUTTON_LEFT, false)))
                                                                                                     .WillOnce(testing::Return(true));

    EXPECT_CALL(del, onMouseRelease(MouseButtonReleasedEvent(glm::vec2(-1), GLFW_MOUSE_BUTTON_LEFT, true)));

    Engine::getInputManager()->addMouseDelegate(&del);

    auto screensize = Engine::getWindowSize();

    mock.mouse_pos_callback_(nullptr, 500, screensize.y - 200);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
    mock.mouse_enter_callback_(nullptr, GL_FALSE);

    testing::Mock::VerifyAndClearExpectations(&del);

    EXPECT_CALL(del, onMouseRelease(testing::_)).Times(0);

    mock.mouse_enter_callback_(nullptr, GL_TRUE);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);

    Engine::cleanup();
}

TEST(TestInputManager, TestMouseDelegatePriorityChange) {
    GlfwMock mock;
    Engine::setup(true, true);

    MockMouseDelegate del1(9);
    MockMouseDelegate del2(7);
    MockMouseDelegate del3(8);

    testing::Sequence s;

    EXPECT_CALL(del1, onMouseDown(testing::_)).Times(0);

    EXPECT_CALL(del2, onMouseDown(MouseButtonPressedEvent(glm::vec2(-1), GLFW_MOUSE_BUTTON_LEFT, true))).InSequence(s)
        .WillOnce(testing::Return(false));

    EXPECT_CALL(del3, onMouseDown(MouseButtonPressedEvent(glm::vec2(-1), GLFW_MOUSE_BUTTON_LEFT, true))).InSequence(s)
        .WillOnce(testing::Return(true));


    Engine::getInputManager()->addMouseDelegate(&del1);
    Engine::getInputManager()->addMouseDelegate(&del2);
    Engine::getInputManager()->addMouseDelegate(&del3);

    del1.setMouseDelegatePriority(5);
    del2.setMouseDelegatePriority(8);
    del3.setMouseDelegatePriority(7);

    Engine::getInputManager()->sortDelegates();

    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);


    Engine::cleanup();
}

TEST(TestInputManager, TestKeyboardDelegate) {
    GlfwMock mock;
    Engine::setup(true, true);

    MockKeyboardDelegate del1(5);
    MockKeyboardDelegate del2(8);
    MockKeyboardDelegate del3(7);

    testing::Sequence s;

    EXPECT_CALL(del1, onKeyPressed(testing::_)).Times(0);

    EXPECT_CALL(del2, onKeyPressed(KeyPressedEvent(GLFW_KEY_ENTER, 234, 0))).InSequence(s)
        .WillOnce(testing::Return(false));

    EXPECT_CALL(del3, onKeyPressed(KeyPressedEvent(GLFW_KEY_ENTER, 234, 0))).InSequence(s)
        .WillOnce(testing::Return(true));


    Engine::getInputManager()->addKeyboardDelegate(&del1);
    Engine::getInputManager()->addKeyboardDelegate(&del2);
    Engine::getInputManager()->addKeyboardDelegate(&del3);

    mock.key_callback_(nullptr, GLFW_KEY_ENTER, 234, GLFW_PRESS, 0);


    Engine::cleanup();
}

TEST(TestInputManager, TestKeyboardDelegateMulti) {
    GlfwMock mock;
    Engine::setup(true, true);

    MockKeyboardDelegate del1(5);
    MockKeyboardDelegate del2(8);
    MockKeyboardDelegate del3(7);

    testing::Sequence s;

    EXPECT_CALL(del1, onKeyPressed(testing::_)).Times(0);

    EXPECT_CALL(del2, onKeyPressed(KeyPressedEvent(GLFW_KEY_ENTER, 234, 0))).InSequence(s)
        .WillOnce(testing::Return(false));

    EXPECT_CALL(del3, onKeyPressed(KeyPressedEvent(GLFW_KEY_ENTER, 234, 0))).InSequence(s)
        .WillOnce(testing::Return(true));

    EXPECT_CALL(del2, onKeyPressed(KeyPressedEvent(GLFW_KEY_0, 234, 0))).InSequence(s)
        .WillOnce(testing::Return(true));


    Engine::getInputManager()->addKeyboardDelegate(&del1);
    Engine::getInputManager()->addKeyboardDelegate(&del2);
    Engine::getInputManager()->addKeyboardDelegate(&del3);

    mock.key_callback_(nullptr, GLFW_KEY_ENTER, 234, GLFW_PRESS, 0);
    mock.key_callback_(nullptr, GLFW_KEY_0, 234, GLFW_PRESS, 0);


    Engine::cleanup();
}

TEST(TestInputManager, TestKeyboardDelegateRepeat) {
    GlfwMock mock;
    Engine::setup(true, true);

    MockKeyboardDelegate del1(5);
    MockKeyboardDelegate del2(8);
    MockKeyboardDelegate del3(7);

    testing::Sequence s;

    EXPECT_CALL(del1, onKeyPressed(testing::_)).Times(0);

    EXPECT_CALL(del2, onKeyPressed(KeyPressedEvent(GLFW_KEY_ENTER, 234, 0))).InSequence(s)
        .WillOnce(testing::Return(false));

    EXPECT_CALL(del3, onKeyPressed(KeyPressedEvent(GLFW_KEY_ENTER, 234, 0))).InSequence(s)
        .WillOnce(testing::Return(true));

    EXPECT_CALL(del3, onKeyRepeat(KeyRepeatEvent(GLFW_KEY_ENTER, 234, 0))).Times(2).InSequence(s);


    Engine::getInputManager()->addKeyboardDelegate(&del1);
    Engine::getInputManager()->addKeyboardDelegate(&del2);
    Engine::getInputManager()->addKeyboardDelegate(&del3);

    mock.key_callback_(nullptr, GLFW_KEY_ENTER, 234, GLFW_PRESS, 0);
    mock.key_callback_(nullptr, GLFW_KEY_ENTER, 234, GLFW_REPEAT, 0);
    mock.key_callback_(nullptr, GLFW_KEY_ENTER, 234, GLFW_REPEAT, 0);


    Engine::cleanup();
}

TEST(TestInputManager, TestKeyboardDelegateRelease) {
    GlfwMock mock;
    Engine::setup(true, true);

    MockKeyboardDelegate del1(5);
    MockKeyboardDelegate del2(8);
    MockKeyboardDelegate del3(7);

    testing::Sequence s;

    EXPECT_CALL(del1, onKeyPressed(testing::_)).Times(0);

    EXPECT_CALL(del2, onKeyPressed(KeyPressedEvent(GLFW_KEY_ENTER, 234, 0))).InSequence(s)
        .WillOnce(testing::Return(false));

    EXPECT_CALL(del3, onKeyPressed(KeyPressedEvent(GLFW_KEY_ENTER, 234, 0))).InSequence(s)
        .WillOnce(testing::Return(true));

    EXPECT_CALL(del3, onKeyRepeat(KeyRepeatEvent(GLFW_KEY_ENTER, 234, 0))).Times(2).InSequence(s);

    EXPECT_CALL(del3, onKeyRelease(KeyReleasedEvent(GLFW_KEY_ENTER, 234, 0))).InSequence(s);

    Engine::getInputManager()->addKeyboardDelegate(&del1);
    Engine::getInputManager()->addKeyboardDelegate(&del2);
    Engine::getInputManager()->addKeyboardDelegate(&del3);

    mock.key_callback_(nullptr, GLFW_KEY_ENTER, 234, GLFW_PRESS, 0);
    mock.key_callback_(nullptr, GLFW_KEY_ENTER, 234, GLFW_REPEAT, 0);
    mock.key_callback_(nullptr, GLFW_KEY_ENTER, 234, GLFW_REPEAT, 0);
    mock.key_callback_(nullptr, GLFW_KEY_ENTER, 234, GLFW_RELEASE, 0);

    Engine::cleanup();
}

TEST(TestInputManager, TestKeyboardDelegatePriorityChange) {
    GlfwMock mock;
    Engine::setup(true, true);

    MockKeyboardDelegate del1(23);
    MockKeyboardDelegate del2(2);
    MockKeyboardDelegate del3(7);

    testing::Sequence s;

    EXPECT_CALL(del1, onKeyPressed(testing::_)).Times(0);

    EXPECT_CALL(del2, onKeyPressed(KeyPressedEvent(GLFW_KEY_ENTER, 234, 0))).InSequence(s)
        .WillOnce(testing::Return(false));

    EXPECT_CALL(del3, onKeyPressed(KeyPressedEvent(GLFW_KEY_ENTER, 234, 0))).InSequence(s)
        .WillOnce(testing::Return(true));

    EXPECT_CALL(del3, onKeyRepeat(KeyRepeatEvent(GLFW_KEY_ENTER, 234, 0))).Times(2).InSequence(s);

    EXPECT_CALL(del3, onKeyRelease(KeyReleasedEvent(GLFW_KEY_ENTER, 234, 0))).InSequence(s);

    Engine::getInputManager()->addKeyboardDelegate(&del1);
    Engine::getInputManager()->addKeyboardDelegate(&del2);
    Engine::getInputManager()->addKeyboardDelegate(&del3);

    del1.setKeyboardDelegatePriority(5);
    del2.setKeyboardDelegatePriority(8);
    del3.setKeyboardDelegatePriority(7);

    Engine::getInputManager()->sortDelegates();

    mock.key_callback_(nullptr, GLFW_KEY_ENTER, 234, GLFW_PRESS, 0);
    mock.key_callback_(nullptr, GLFW_KEY_ENTER, 234, GLFW_REPEAT, 0);

    del3.setKeyboardDelegatePriority(0);

    Engine::getInputManager()->sortDelegates();

    mock.key_callback_(nullptr, GLFW_KEY_ENTER, 234, GLFW_REPEAT, 0);
    mock.key_callback_(nullptr, GLFW_KEY_ENTER, 234, GLFW_RELEASE, 0);

    Engine::cleanup();
}

TEST(TestInputManager, TestKeyboardDelegateSwallow) {
    GlfwMock mock;
    Engine::setup(true, true);

    MockKeyboardDelegate del1(5);
    MockKeyboardDelegate del2(8);
    MockKeyboardDelegate del3(7);

    del2.setSwallowsEvents(false);

    testing::Sequence s;

    EXPECT_CALL(del1, onKeyPressed(testing::_)).Times(0);

    EXPECT_CALL(del2, onKeyPressed(KeyPressedEvent(GLFW_KEY_ENTER, 234, 0))).InSequence(s)
        .WillOnce(testing::Return(true));

    EXPECT_CALL(del3, onKeyPressed(KeyPressedEvent(GLFW_KEY_ENTER, 234, 0))).InSequence(s)
        .WillOnce(testing::Return(true));

    EXPECT_CALL(del2, onKeyRepeat(KeyRepeatEvent(GLFW_KEY_ENTER, 234, 0))).InSequence(s);

    EXPECT_CALL(del3, onKeyRepeat(KeyRepeatEvent(GLFW_KEY_ENTER, 234, 0))).InSequence(s);
   
    EXPECT_CALL(del2, onKeyRepeat(KeyRepeatEvent(GLFW_KEY_ENTER, 234, 0))).InSequence(s);

    EXPECT_CALL(del3, onKeyRepeat(KeyRepeatEvent(GLFW_KEY_ENTER, 234, 0))).InSequence(s);

    EXPECT_CALL(del2, onKeyRelease(KeyReleasedEvent(GLFW_KEY_ENTER, 234, 0))).InSequence(s);

    EXPECT_CALL(del3, onKeyRelease(KeyReleasedEvent(GLFW_KEY_ENTER, 234, 0))).InSequence(s);



    Engine::getInputManager()->addKeyboardDelegate(&del1);
    Engine::getInputManager()->addKeyboardDelegate(&del3);
    Engine::getInputManager()->addKeyboardDelegate(&del2);


    mock.key_callback_(nullptr, GLFW_KEY_ENTER, 234, GLFW_PRESS, 0);
    mock.key_callback_(nullptr, GLFW_KEY_ENTER, 234, GLFW_REPEAT, 0);
    mock.key_callback_(nullptr, GLFW_KEY_ENTER, 234, GLFW_REPEAT, 0);
    mock.key_callback_(nullptr, GLFW_KEY_ENTER, 234, GLFW_RELEASE, 0);

    Engine::cleanup();
}