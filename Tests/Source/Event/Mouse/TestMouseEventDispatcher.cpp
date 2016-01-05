#include <glfwmock.h>
#include <FTEngine.h>
#include <Event/FTEventManager.h>
#include <Event/Mouse/FTMouseEventDispatcher.h>

class MockMouseEventListener {
public:
    MOCK_METHOD1(mouseMoveEvent, void(const FTMouseMoveEvent&));
    MOCK_METHOD1(mouseEnterEvent, void(const FTMouseEnterEvent&));
    MOCK_METHOD1(mouseExitEvent, void(const FTMouseExitEvent&));
    MOCK_METHOD1(mouseButtonPressedEvent, void(const FTMouseButtonPressedEvent&));
    MOCK_METHOD1(mouseButtonReleasedEvent, void(const FTMouseButtonReleasedEvent&));
    MOCK_METHOD1(mouseScrollEvent, void(const FTMouseScrollEvent&));
};

TEST(TestMouseEventDispatcher, TestMouseMove) {
    GlfwMock mock;
    FTEngine::setup(true);
    MockMouseEventListener listener;

    auto move_delegate = Gallant::Delegate1<const FTMouseMoveEvent&>(&listener, &MockMouseEventListener::mouseMoveEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTMouseEventDispatcher>()->registerDelegate(move_delegate);

    testing::InSequence s;

    EXPECT_CALL(listener, mouseMoveEvent(FTMouseMoveEvent(200,100,0,0)));
    EXPECT_CALL(listener, mouseMoveEvent(FTMouseMoveEvent(240, 80, 40, -20)));

    auto screensize = FTEngine::getWindowSize();

    mock.mouse_pos_callback_(nullptr, 200, screensize.y - 100);
    mock.mouse_pos_callback_(nullptr, 240, screensize.y - 80);

    FTEngine::cleanup();
}

TEST(TestMouseEventDispatcher, TestMouseEnterExitEventEvent) {
    GlfwMock mock;
    FTEngine::setup(true);
    MockMouseEventListener listener;

    auto enter_delegate = Gallant::Delegate1<const FTMouseEnterEvent&>(&listener, &MockMouseEventListener::mouseEnterEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTMouseEventDispatcher>()->registerDelegate(enter_delegate);
    auto exit_delegate = Gallant::Delegate1<const FTMouseExitEvent&>(&listener, &MockMouseEventListener::mouseExitEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTMouseEventDispatcher>()->registerDelegate(exit_delegate);

    testing::InSequence s;

    EXPECT_CALL(listener, mouseEnterEvent(testing::_));
    EXPECT_CALL(listener, mouseExitEvent(testing::_));

    mock.mouse_enter_callback_(nullptr, GL_TRUE);
    mock.mouse_enter_callback_(nullptr, GL_FALSE);

    FTEngine::cleanup();
}

TEST(TestMouseEventDispatcher, TestEnterExitPosPurge) {
    GlfwMock mock;
    FTEngine::setup(true);
    MockMouseEventListener listener;

    auto enter_delegate = Gallant::Delegate1<const FTMouseEnterEvent&>(&listener, &MockMouseEventListener::mouseEnterEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTMouseEventDispatcher>()->registerDelegate(enter_delegate);
    auto exit_delegate = Gallant::Delegate1<const FTMouseExitEvent&>(&listener, &MockMouseEventListener::mouseExitEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTMouseEventDispatcher>()->registerDelegate(exit_delegate);
    auto move_delegate = Gallant::Delegate1<const FTMouseMoveEvent&>(&listener, &MockMouseEventListener::mouseMoveEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTMouseEventDispatcher>()->registerDelegate(move_delegate);

    testing::InSequence s;


    EXPECT_CALL(listener, mouseMoveEvent(FTMouseMoveEvent(200, 100, 0, 0)));
    EXPECT_CALL(listener, mouseEnterEvent(testing::_));
    EXPECT_CALL(listener, mouseExitEvent(testing::_));
    EXPECT_CALL(listener, mouseMoveEvent(FTMouseMoveEvent(240, 80, 0, 0)));

    auto screensize = FTEngine::getWindowSize();

    mock.mouse_pos_callback_(nullptr, 200, screensize.y - 100);

    mock.mouse_enter_callback_(nullptr, GL_TRUE);
    mock.mouse_enter_callback_(nullptr, GL_FALSE);

    mock.mouse_pos_callback_(nullptr, 240, screensize.y - 80);

    FTEngine::cleanup();
}

TEST(TestMouseEventDispatcher, TestMouseButtonSimple) {
    GlfwMock mock;
    FTEngine::setup(true);
    MockMouseEventListener listener;

    auto move_delegate = Gallant::Delegate1<const FTMouseMoveEvent&>(&listener, &MockMouseEventListener::mouseMoveEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTMouseEventDispatcher>()->registerDelegate(move_delegate);

    auto pressed_delegate = Gallant::Delegate1<const FTMouseButtonPressedEvent&>(&listener, &MockMouseEventListener::mouseButtonPressedEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTMouseEventDispatcher>()->registerDelegate(pressed_delegate);

    auto released_delegate = Gallant::Delegate1<const FTMouseButtonReleasedEvent&>(&listener, &MockMouseEventListener::mouseButtonReleasedEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTMouseEventDispatcher>()->registerDelegate(released_delegate);

    testing::InSequence s;

    EXPECT_CALL(listener, mouseMoveEvent(FTMouseMoveEvent(200, 100, 0, 0)));
    EXPECT_CALL(listener, mouseMoveEvent(FTMouseMoveEvent(240, 80, 40, -20)));
    EXPECT_CALL(listener, mouseButtonPressedEvent(FTMouseButtonPressedEvent(240, 80, GLFW_MOUSE_BUTTON_LEFT, false)));
    EXPECT_CALL(listener, mouseButtonReleasedEvent(FTMouseButtonReleasedEvent(240, 80, GLFW_MOUSE_BUTTON_LEFT, false)));

    auto screensize = FTEngine::getWindowSize();

    mock.mouse_pos_callback_(nullptr, 200, screensize.y - 100);
    mock.mouse_pos_callback_(nullptr, 240, screensize.y - 80);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);


    FTEngine::cleanup();
}

TEST(TestMouseEventDispatcher, TestMouseButtonExit) {
    GlfwMock mock;
    FTEngine::setup(true);
    MockMouseEventListener listener;

    auto move_delegate = Gallant::Delegate1<const FTMouseMoveEvent&>(&listener, &MockMouseEventListener::mouseMoveEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTMouseEventDispatcher>()->registerDelegate(move_delegate);

    auto pressed_delegate = Gallant::Delegate1<const FTMouseButtonPressedEvent&>(&listener, &MockMouseEventListener::mouseButtonPressedEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTMouseEventDispatcher>()->registerDelegate(pressed_delegate);

    auto released_delegate = Gallant::Delegate1<const FTMouseButtonReleasedEvent&>(&listener, &MockMouseEventListener::mouseButtonReleasedEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTMouseEventDispatcher>()->registerDelegate(released_delegate);

    testing::InSequence s;

    EXPECT_CALL(listener, mouseMoveEvent(FTMouseMoveEvent(200, 100, 0, 0)));
    EXPECT_CALL(listener, mouseMoveEvent(FTMouseMoveEvent(240, 80, 40, -20)));
    EXPECT_CALL(listener, mouseButtonPressedEvent(FTMouseButtonPressedEvent(240, 80, GLFW_MOUSE_BUTTON_LEFT, false)));
    EXPECT_CALL(listener, mouseButtonReleasedEvent(FTMouseButtonReleasedEvent(-1, -1, GLFW_MOUSE_BUTTON_LEFT, true)));

    auto screensize = FTEngine::getWindowSize();

    mock.mouse_pos_callback_(nullptr, 200, screensize.y - 100);
    mock.mouse_pos_callback_(nullptr, 240, screensize.y - 80);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
    mock.mouse_enter_callback_(nullptr, GL_FALSE);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);


    FTEngine::cleanup();
}

TEST(TestMouseEventDispatcher, TestMouseScroll) {
    GlfwMock mock;
    FTEngine::setup(true);
    MockMouseEventListener listener;

    auto move_delegate = Gallant::Delegate1<const FTMouseMoveEvent&>(&listener, &MockMouseEventListener::mouseMoveEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTMouseEventDispatcher>()->registerDelegate(move_delegate);

    FTEngine::getEventManager()->registerDelegate<FTMouseEventDispatcher>(&listener, &MockMouseEventListener::mouseScrollEvent);
        
    testing::InSequence s;

    EXPECT_CALL(listener, mouseScrollEvent(FTMouseScrollEvent(-1, -1, 20, 30, true)));
    EXPECT_CALL(listener, mouseMoveEvent(FTMouseMoveEvent(200, 100, 0, 0)));
    EXPECT_CALL(listener, mouseScrollEvent(FTMouseScrollEvent(200, 100, 50, 22, false)));
    EXPECT_CALL(listener, mouseMoveEvent(FTMouseMoveEvent(240, 80, 40, -20)));

    auto screensize = FTEngine::getWindowSize();

    mock.mouse_scroll_callback_(nullptr, 20, 30);
    mock.mouse_pos_callback_(nullptr, 200, screensize.y - 100);
    mock.mouse_scroll_callback_(nullptr, 50, 22);
    mock.mouse_pos_callback_(nullptr, 240, screensize.y - 80);


    FTEngine::cleanup();
}
