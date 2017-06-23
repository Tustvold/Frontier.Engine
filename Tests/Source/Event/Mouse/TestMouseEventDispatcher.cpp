#include <glfwmock.h>
#include <Engine.h>
#include <Event/EventManager.h>
#include <Event/Mouse/MouseEventDispatcher.h>
#include <gmock/gmock.h>

USING_NS_FT

class MockMouseEventListener {
public:
    MOCK_METHOD1(mouseMoveEvent, void(const MouseMoveEvent&));
    MOCK_METHOD1(mouseEnterEvent, void(const MouseEnterEvent&));
    MOCK_METHOD1(mouseExitEvent, void(const MouseExitEvent&));
    MOCK_METHOD1(mouseButtonPressedEvent, void(const MouseButtonPressedEvent&));
    MOCK_METHOD1(mouseButtonReleasedEvent, void(const MouseButtonReleasedEvent&));
    MOCK_METHOD1(mouseScrollEvent, void(const MouseScrollEvent&));
};

TEST(TestMouseEventDispatcher, TestMouseMove) {
    GlfwMock mock;
    Engine::setup(true, true);
    MockMouseEventListener listener;

    auto move_delegate = Gallant::Delegate1<const MouseMoveEvent&>(&listener, &MockMouseEventListener::mouseMoveEvent);
    Engine::getEventManager()->getEventDispatcher<MouseEventDispatcher>()->registerDelegate(move_delegate);

    testing::InSequence s;

    EXPECT_CALL(listener, mouseMoveEvent(MouseMoveEvent(glm::vec2(200,100),glm::vec2(0,0))));
    EXPECT_CALL(listener, mouseMoveEvent(MouseMoveEvent(glm::vec2(240,80), glm::vec2(40, -20))));

    auto screensize = Engine::getWindowSize();

    mock.mouse_pos_callback_(nullptr, 200, screensize.y - 100);
    mock.mouse_pos_callback_(nullptr, 240, screensize.y - 80);

    Engine::cleanup();
}

TEST(TestMouseEventDispatcher, TestMouseEnterExitEventEvent) {
    GlfwMock mock;
    Engine::setup(true, true);
    MockMouseEventListener listener;

    auto enter_delegate = Gallant::Delegate1<const MouseEnterEvent&>(&listener, &MockMouseEventListener::mouseEnterEvent);
    Engine::getEventManager()->getEventDispatcher<MouseEventDispatcher>()->registerDelegate(enter_delegate);
    auto exit_delegate = Gallant::Delegate1<const MouseExitEvent&>(&listener, &MockMouseEventListener::mouseExitEvent);
    Engine::getEventManager()->getEventDispatcher<MouseEventDispatcher>()->registerDelegate(exit_delegate);

    testing::InSequence s;

    EXPECT_CALL(listener, mouseEnterEvent(testing::_));
    EXPECT_CALL(listener, mouseExitEvent(testing::_));

    mock.mouse_enter_callback_(nullptr, GL_TRUE);
    mock.mouse_enter_callback_(nullptr, GL_FALSE);

    Engine::cleanup();
}

TEST(TestMouseEventDispatcher, TestEnterExitPosPurge) {
    GlfwMock mock;
    Engine::setup(true, true);
    MockMouseEventListener listener;

    auto enter_delegate = Gallant::Delegate1<const MouseEnterEvent&>(&listener, &MockMouseEventListener::mouseEnterEvent);
    Engine::getEventManager()->getEventDispatcher<MouseEventDispatcher>()->registerDelegate(enter_delegate);
    auto exit_delegate = Gallant::Delegate1<const MouseExitEvent&>(&listener, &MockMouseEventListener::mouseExitEvent);
    Engine::getEventManager()->getEventDispatcher<MouseEventDispatcher>()->registerDelegate(exit_delegate);
    auto move_delegate = Gallant::Delegate1<const MouseMoveEvent&>(&listener, &MockMouseEventListener::mouseMoveEvent);
    Engine::getEventManager()->getEventDispatcher<MouseEventDispatcher>()->registerDelegate(move_delegate);

    testing::InSequence s;


    EXPECT_CALL(listener, mouseMoveEvent(MouseMoveEvent(glm::vec2(200,100), glm::vec2(0, 0))));
    EXPECT_CALL(listener, mouseEnterEvent(testing::_));
    EXPECT_CALL(listener, mouseExitEvent(testing::_));
    EXPECT_CALL(listener, mouseMoveEvent(MouseMoveEvent(glm::vec2(240,80), glm::vec2(0, 0))));

    auto screensize = Engine::getWindowSize();

    mock.mouse_pos_callback_(nullptr, 200, screensize.y - 100);

    mock.mouse_enter_callback_(nullptr, GL_TRUE);
    mock.mouse_enter_callback_(nullptr, GL_FALSE);

    mock.mouse_pos_callback_(nullptr, 240, screensize.y - 80);

    Engine::cleanup();
}

TEST(TestMouseEventDispatcher, TestMouseButtonSimple) {
    GlfwMock mock;
    Engine::setup(true, true);
    MockMouseEventListener listener;

    auto move_delegate = Gallant::Delegate1<const MouseMoveEvent&>(&listener, &MockMouseEventListener::mouseMoveEvent);
    Engine::getEventManager()->getEventDispatcher<MouseEventDispatcher>()->registerDelegate(move_delegate);

    auto pressed_delegate = Gallant::Delegate1<const MouseButtonPressedEvent&>(&listener, &MockMouseEventListener::mouseButtonPressedEvent);
    Engine::getEventManager()->getEventDispatcher<MouseEventDispatcher>()->registerDelegate(pressed_delegate);

    auto released_delegate = Gallant::Delegate1<const MouseButtonReleasedEvent&>(&listener, &MockMouseEventListener::mouseButtonReleasedEvent);
    Engine::getEventManager()->getEventDispatcher<MouseEventDispatcher>()->registerDelegate(released_delegate);

    testing::InSequence s;

    EXPECT_CALL(listener, mouseMoveEvent(MouseMoveEvent(glm::vec2(200,100), glm::vec2(0, 0))));
    EXPECT_CALL(listener, mouseMoveEvent(MouseMoveEvent(glm::vec2(240,80), glm::vec2(40, -20))));
    EXPECT_CALL(listener, mouseButtonPressedEvent(MouseButtonPressedEvent(glm::vec2(240, 80), GLFW_MOUSE_BUTTON_LEFT, false)));
    EXPECT_CALL(listener, mouseButtonReleasedEvent(MouseButtonReleasedEvent(glm::vec2(240, 80), GLFW_MOUSE_BUTTON_LEFT, false)));

    auto screensize = Engine::getWindowSize();

    mock.mouse_pos_callback_(nullptr, 200, screensize.y - 100);
    mock.mouse_pos_callback_(nullptr, 240, screensize.y - 80);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);


    Engine::cleanup();
}

TEST(TestMouseEventDispatcher, TestMouseButtonExit) {
    GlfwMock mock;
    Engine::setup(true, true);
    MockMouseEventListener listener;

    auto move_delegate = Gallant::Delegate1<const MouseMoveEvent&>(&listener, &MockMouseEventListener::mouseMoveEvent);
    Engine::getEventManager()->getEventDispatcher<MouseEventDispatcher>()->registerDelegate(move_delegate);

    auto pressed_delegate = Gallant::Delegate1<const MouseButtonPressedEvent&>(&listener, &MockMouseEventListener::mouseButtonPressedEvent);
    Engine::getEventManager()->getEventDispatcher<MouseEventDispatcher>()->registerDelegate(pressed_delegate);

    auto released_delegate = Gallant::Delegate1<const MouseButtonReleasedEvent&>(&listener, &MockMouseEventListener::mouseButtonReleasedEvent);
    Engine::getEventManager()->getEventDispatcher<MouseEventDispatcher>()->registerDelegate(released_delegate);

    testing::InSequence s;

    EXPECT_CALL(listener, mouseMoveEvent(MouseMoveEvent(glm::vec2(200,100), glm::vec2(0, 0))));
    EXPECT_CALL(listener, mouseMoveEvent(MouseMoveEvent(glm::vec2(240,80), glm::vec2(40, -20))));
    EXPECT_CALL(listener, mouseButtonPressedEvent(MouseButtonPressedEvent(glm::vec2(240, 80), GLFW_MOUSE_BUTTON_LEFT, false)));
    EXPECT_CALL(listener, mouseButtonReleasedEvent(MouseButtonReleasedEvent(glm::vec2(-1, -1), GLFW_MOUSE_BUTTON_LEFT, true)));

    auto screensize = Engine::getWindowSize();

    mock.mouse_pos_callback_(nullptr, 200, screensize.y - 100);
    mock.mouse_pos_callback_(nullptr, 240, screensize.y - 80);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
    mock.mouse_enter_callback_(nullptr, GL_FALSE);
    mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);


    Engine::cleanup();
}

TEST(TestMouseEventDispatcher, TestMouseScroll) {
    GlfwMock mock;
    Engine::setup(true, true);
    MockMouseEventListener listener;

    auto move_delegate = Gallant::Delegate1<const MouseMoveEvent&>(&listener, &MockMouseEventListener::mouseMoveEvent);
    Engine::getEventManager()->getEventDispatcher<MouseEventDispatcher>()->registerDelegate(move_delegate);

    Engine::getEventManager()->registerDelegate<MouseEventDispatcher>(&listener, &MockMouseEventListener::mouseScrollEvent);

    testing::InSequence s;

    EXPECT_CALL(listener, mouseScrollEvent(MouseScrollEvent(glm::vec2(-1), glm::vec2(20,30), true)));
    EXPECT_CALL(listener, mouseMoveEvent(MouseMoveEvent(glm::vec2(200,100), glm::vec2(0, 0))));
    EXPECT_CALL(listener, mouseScrollEvent(MouseScrollEvent(glm::vec2(200,100), glm::vec2(50,22), false)));
    EXPECT_CALL(listener, mouseMoveEvent(MouseMoveEvent(glm::vec2(240,80), glm::vec2(40, -20))));

    auto screensize = Engine::getWindowSize();

    mock.mouse_scroll_callback_(nullptr, 20, 30);
    mock.mouse_pos_callback_(nullptr, 200, screensize.y - 100);
    mock.mouse_scroll_callback_(nullptr, 50, 22);
    mock.mouse_pos_callback_(nullptr, 240, screensize.y - 80);


    Engine::cleanup();
}

