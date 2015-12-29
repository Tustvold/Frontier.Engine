#include <glfwmock.h>
#include <FTEngine.h>
#include <Event/Input/FTInputManager.h>
#include <Mock/MockEngineEventDispatcher.h>

class MockMouseDelegate : public FTMouseDelegate {
public:
    bool getMouseDelegateEnabled() const override {
        return true;
    }

    MOCK_METHOD1(onMouseDown, bool(const FTMouseButtonPressedEvent&));
    MOCK_METHOD2(onMouseDrag, void(const FTMouseMoveEvent&, int));
    MOCK_METHOD1(onMouseRelease, void(const FTMouseButtonReleasedEvent&));

    MOCK_METHOD1(onMouseMove, bool(const FTMouseMoveEvent&));

    MockMouseDelegate(int priority) : FTMouseDelegate(priority) {
    }

    

};

TEST(TestInputManager, TestKeyStatePressed) {
    GlfwMock mock;
    FTEngine::setup(true);

    auto state = FTEngine::getInputManager()->getKeyState("Forward", GLFW_KEY_0);

    EXPECT_FALSE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_0, 23, GLFW_PRESS, 0);

    EXPECT_TRUE(state->isPressed());

    FTEngine::cleanup();
}

TEST(TestInputManager, TestKeyStateReleased) {
    GlfwMock mock;
    FTEngine::init();
    auto engine_event_dispatcher = std::make_shared<MockEngineEventDispatcher>();
    FTEngine::getEventManager()->registerDispatcher(std::static_pointer_cast<FTEngineEventDispatcher>(engine_event_dispatcher));
    FTEngine::setup(true);

    auto state = FTEngine::getInputManager()->getKeyState("Forward", GLFW_KEY_0);

    EXPECT_FALSE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_0, 23, GLFW_PRESS, 0);

    EXPECT_TRUE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_0, 23, GLFW_RELEASE, 0);

    // We don't expect the state to get updated until the next world tick
    EXPECT_TRUE(state->isPressed());

    engine_event_dispatcher->raiseEvent(FTUpdateEvent(1.0));

    EXPECT_FALSE(state->isPressed());

    FTEngine::cleanup();
}

TEST(TestInputManager, TestMapKey) {
    GlfwMock mock;
    FTEngine::init();
    auto engine_event_dispatcher = std::make_shared<MockEngineEventDispatcher>();
    FTEngine::getEventManager()->registerDispatcher(std::static_pointer_cast<FTEngineEventDispatcher>(engine_event_dispatcher));
    FTEngine::setup(true);

    auto state = FTEngine::getInputManager()->getKeyState("Forward");
    FTEngine::getInputManager()->addMapping("Forward", GLFW_KEY_0);

    EXPECT_FALSE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_0, 23, GLFW_PRESS, 0);

    EXPECT_TRUE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_0, 23, GLFW_RELEASE, 0);

    // We don't expect the state to get updated until the next world tick
    EXPECT_TRUE(state->isPressed());

    engine_event_dispatcher->raiseEvent(FTUpdateEvent(1.0));

    EXPECT_FALSE(state->isPressed());

    FTEngine::cleanup();
}

TEST(TestInputManager, TestMouseDown) {
    GlfwMock mock;
    FTEngine::setup(true);

    MockMouseDelegate del1(5);
    MockMouseDelegate del2(8);
    MockMouseDelegate del3(7);

    EXPECT_CALL(del1, onMouseDown(testing::_)).Times(0);

    EXPECT_CALL(del2, onMouseDown(FTMouseButtonPressedEvent(-1, -1, GLFW_MOUSE_BUTTON_LEFT, true)))
                                                                                                             .WillOnce(testing::Return(true));

    EXPECT_CALL(del3, onMouseDown(testing::_)).Times(0);


    FTEngine::getInputManager()->addMouseDelegate(&del1);
    FTEngine::getInputManager()->addMouseDelegate(&del2);
    FTEngine::getInputManager()->addMouseDelegate(&del3);

    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);


    FTEngine::cleanup();
}

TEST(TestInputManager, TestMouseDownChained) {
    GlfwMock mock;
    FTEngine::setup(true);

    MockMouseDelegate del1(5);
    MockMouseDelegate del2(8);
    MockMouseDelegate del3(7);


    EXPECT_CALL(del1, onMouseDown(testing::_)).Times(0);

    EXPECT_CALL(del2, onMouseDown(FTMouseButtonPressedEvent(-1, -1, GLFW_MOUSE_BUTTON_LEFT, true)))
                                                                                                             .WillOnce(testing::Return(false));

    EXPECT_CALL(del3, onMouseDown(FTMouseButtonPressedEvent(-1, -1, GLFW_MOUSE_BUTTON_LEFT, true)))
                                                                                                             .WillOnce(testing::Return(true));


    FTEngine::getInputManager()->addMouseDelegate(&del1);
    FTEngine::getInputManager()->addMouseDelegate(&del2);
    FTEngine::getInputManager()->addMouseDelegate(&del3);

    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);


    FTEngine::cleanup();
}

TEST(TestInputManager, TestMouseMoved) {
    GlfwMock mock;
    FTEngine::setup(true);

    MockMouseDelegate del1(5);
    MockMouseDelegate del2(8);
    MockMouseDelegate del3(7);

    testing::Sequence s;

    EXPECT_CALL(del1, onMouseMove(testing::_)).Times(0);

    EXPECT_CALL(del2, onMouseMove(testing::_)).InSequence(s).WillOnce(testing::Return(false));

    EXPECT_CALL(del3, onMouseMove(testing::_)).InSequence(s).WillOnce(testing::Return(true));

    EXPECT_CALL(del1, onMouseDown(testing::_)).Times(0);

    EXPECT_CALL(del2, onMouseDown(FTMouseButtonPressedEvent(240, 80, GLFW_MOUSE_BUTTON_LEFT, false)))
                                                                                                     .InSequence(s)
                                                                                                     .WillOnce(testing::Return(false));

    EXPECT_CALL(del3, onMouseDown(FTMouseButtonPressedEvent(240, 80, GLFW_MOUSE_BUTTON_LEFT, false)))
                                                                                                     .InSequence(s)
                                                                                                     .WillOnce(testing::Return(true));
    

    EXPECT_CALL(del2, onMouseMove(testing::_)).InSequence(s).WillOnce(testing::Return(true));

    EXPECT_CALL(del1, onMouseDrag(testing::_, testing::_)).Times(0);

    EXPECT_CALL(del2, onMouseDrag(testing::_, testing::_)).Times(0);

    EXPECT_CALL(del3, onMouseDrag(testing::_, GLFW_MOUSE_BUTTON_LEFT)).Times(1).InSequence(s);

    FTEngine::getInputManager()->addMouseDelegate(&del1);
    FTEngine::getInputManager()->addMouseDelegate(&del2);
    FTEngine::getInputManager()->addMouseDelegate(&del3);

    auto screensize = FTEngine::getWindowSize();

    mock.mouse_pos_callback_(nullptr, 240, screensize.y - 80);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
    mock.mouse_pos_callback_(nullptr, 480, screensize.y - 60);

    FTEngine::cleanup();
}

TEST(TestInputManager, TestMouseExit) {
    GlfwMock mock;
    FTEngine::setup(true);

    MockMouseDelegate del1(5);
    MockMouseDelegate del2(8);
    MockMouseDelegate del3(7);

    testing::Sequence s;

    EXPECT_CALL(del2, onMouseMove(testing::_)).InSequence(s).WillOnce(testing::Return(false));

    EXPECT_CALL(del3, onMouseMove(testing::_)).InSequence(s).WillOnce(testing::Return(true));

    EXPECT_CALL(del1, onMouseDown(testing::_)).Times(0);

    EXPECT_CALL(del2, onMouseDown(FTMouseButtonPressedEvent(240, 80, GLFW_MOUSE_BUTTON_LEFT, false)))
                                                                                                     .InSequence(s)
                                                                                                     .WillOnce(testing::Return(false));

    EXPECT_CALL(del3, onMouseDown(FTMouseButtonPressedEvent(240, 80, GLFW_MOUSE_BUTTON_LEFT, false)))
                                                                                                     .InSequence(s)
                                                                                                     .WillOnce(testing::Return(true));
    EXPECT_CALL(del2, onMouseMove(testing::_)).InSequence(s).WillOnce(testing::Return(true));

    EXPECT_CALL(del1, onMouseDrag(testing::_, testing::_)).Times(0);

    EXPECT_CALL(del2, onMouseDrag(testing::_, testing::_)).Times(0);

    EXPECT_CALL(del3, onMouseDrag(testing::_, GLFW_MOUSE_BUTTON_LEFT)).Times(1).InSequence(s);

    EXPECT_CALL(del1, onMouseRelease(testing::_)).Times(0);

    EXPECT_CALL(del2, onMouseRelease(testing::_)).Times(0);

    EXPECT_CALL(del3, onMouseRelease(testing::_)).Times(1).InSequence(s);

    EXPECT_CALL(del2, onMouseMove(testing::_)).InSequence(s).WillOnce(testing::Return(true));

    FTEngine::getInputManager()->addMouseDelegate(&del1);
    FTEngine::getInputManager()->addMouseDelegate(&del2);
    FTEngine::getInputManager()->addMouseDelegate(&del3);

    auto screensize = FTEngine::getWindowSize();

    mock.mouse_pos_callback_(nullptr, 240, screensize.y - 80);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
    mock.mouse_pos_callback_(nullptr, 480, screensize.y - 60);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);
    mock.mouse_pos_callback_(nullptr, 530, screensize.y - 60);


    FTEngine::cleanup();
}

TEST(TestInputManager, TestMultipleMouseButtons) {
    GlfwMock mock;
    FTEngine::setup(true);

    MockMouseDelegate del(5);

    testing::Sequence s;

    EXPECT_CALL(del, onMouseMove(testing::_)).InSequence(s).WillOnce(testing::Return(true));

    EXPECT_CALL(del, onMouseDown(FTMouseButtonPressedEvent(240, 80, GLFW_MOUSE_BUTTON_LEFT, false)))
                                                                                                    .InSequence(s)
                                                                                                    .WillOnce(testing::Return(true));

    EXPECT_CALL(del, onMouseDown(FTMouseButtonPressedEvent(240, 80, GLFW_MOUSE_BUTTON_RIGHT, false)))
                                                                                                     .InSequence(s)
                                                                                                     .WillOnce(testing::Return(true));

    EXPECT_CALL(del, onMouseMove(testing::_)).InSequence(s).WillOnce(testing::Return(true));


    EXPECT_CALL(del, onMouseDrag(testing::_, GLFW_MOUSE_BUTTON_LEFT))
                                                                     .Times(1)
                                                                     .InSequence(s);


    EXPECT_CALL(del, onMouseDrag(testing::_, GLFW_MOUSE_BUTTON_RIGHT))
                                                                      .Times(1)
                                                                      .InSequence(s);

    EXPECT_CALL(del, onMouseRelease(FTMouseButtonReleasedEvent(480, 60, GLFW_MOUSE_BUTTON_RIGHT, false)))
                                                                                                         .Times(1)
                                                                                                         .InSequence(s);

    EXPECT_CALL(del, onMouseRelease(FTMouseButtonReleasedEvent(480, 60, GLFW_MOUSE_BUTTON_LEFT, false)))
                                                                                                        .Times(1)
                                                                                                        .InSequence(s);

    EXPECT_CALL(del, onMouseMove(testing::_)).InSequence(s).WillOnce(testing::Return(true));


    FTEngine::getInputManager()->addMouseDelegate(&del);

    auto screensize = FTEngine::getWindowSize();

    mock.mouse_pos_callback_(nullptr, 240, screensize.y - 80);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS, 0);
    mock.mouse_pos_callback_(nullptr, 480, screensize.y - 60);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_RIGHT, GLFW_RELEASE, 0);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);
    mock.mouse_pos_callback_(nullptr, 530, screensize.y - 60);


    FTEngine::cleanup();
}

TEST(TestInputManager, TestMouseDelegateExit) {
    GlfwMock mock;
    FTEngine::setup(true);

    MockMouseDelegate del(5);

    testing::InSequence s;

    EXPECT_CALL(del, onMouseMove(FTMouseMoveEvent(500, 200, 0, 0))).WillOnce(testing::Return(false));

    EXPECT_CALL(del, onMouseDown(FTMouseButtonPressedEvent(500, 200, GLFW_MOUSE_BUTTON_LEFT, false)))
        .WillOnce(testing::Return(true));

    EXPECT_CALL(del, onMouseRelease(FTMouseButtonReleasedEvent(-1, -1, GLFW_MOUSE_BUTTON_LEFT, true)));

    FTEngine::getInputManager()->addMouseDelegate(&del);

    auto screensize = FTEngine::getWindowSize();

    mock.mouse_pos_callback_(nullptr, 500, screensize.y - 200);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
    mock.mouse_enter_callback_(nullptr, GL_FALSE);

    testing::Mock::VerifyAndClearExpectations(&del);

    EXPECT_CALL(del, onMouseRelease(testing::_)).Times(0);

    mock.mouse_enter_callback_(nullptr, GL_TRUE);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);

    FTEngine::cleanup();
}