#include <glfwmock.h>
#include <FTEngine.h>
#include <Event/FTEventManager.h>
#include <Event/Mouse/FTMouseEventDispatcher.h>

class MockMouseEventListener {
public:
    MOCK_METHOD1(mouseMoveEvent, void(const FTMouseMoveEvent&));
    MOCK_METHOD1(mouseEnterEvent, void(const FTMouseEnterEvent&)); 
    MOCK_METHOD1(mouseExitEvent, void(const FTMouseExitEvent&));

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

    mock.mouse_pos_callback_(nullptr, 200, 100);
    mock.mouse_pos_callback_(nullptr, 240, 80);

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

    mock.mouse_pos_callback_(nullptr, 200, 100);

    mock.mouse_enter_callback_(nullptr, GL_TRUE);
    mock.mouse_enter_callback_(nullptr, GL_FALSE);

    mock.mouse_pos_callback_(nullptr, 240, 80);

    FTEngine::cleanup();
}