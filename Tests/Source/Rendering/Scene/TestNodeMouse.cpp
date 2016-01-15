#include <glfwmock.h>
#include <FTEngine.h>
#include <Event/FTEventManager.h>
#include <Event/Mouse/FTMouseEventDispatcher.h>
#include <Rendering/FTNode.h>
#include <Rendering/FTView.h>
#include <Rendering/FTScene.h>
#include <Rendering/FTDirector.h>

class MockNodeMouse : public FTNode {

public:
    MOCK_METHOD1(onMouseDown, bool(const FTMouseButtonPressedEvent& event));
};

TEST(TestNodeMouse, TestMousePress) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
        auto listener = std::make_shared<MockNodeMouse>();
        auto view = std::make_shared<FTView>();
        auto scene = std::make_shared<FTScene>();
        FTEngine::getDirector()->setCurrentScene(scene, true);
        scene->addView(view);
        view->addChild(listener);

        auto screensize = FTEngine::getWindowSize();

        mock.mouse_pos_callback_(nullptr, 200, screensize.y - 100);

        EXPECT_CALL(*listener, onMouseDown(testing::_)).Times(0);
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
        testing::Mock::VerifyAndClearExpectations(listener.get());

        listener->setMouseInputEnabled(true);
        EXPECT_CALL(*listener, onMouseDown(FTMouseButtonPressedEvent(glm::vec2(200, 100), GLFW_MOUSE_BUTTON_LEFT, false)));
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
        testing::Mock::VerifyAndClearExpectations(listener.get());

        listener->setMouseInputEnabled(false);
        EXPECT_CALL(*listener, onMouseDown(testing::_)).Times(0);
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
        testing::Mock::VerifyAndClearExpectations(listener.get());

        listener->setMouseInputEnabled(true);
        EXPECT_CALL(*listener, onMouseDown(FTMouseButtonPressedEvent(glm::vec2(200, 100), GLFW_MOUSE_BUTTON_LEFT, false)));
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
        testing::Mock::VerifyAndClearExpectations(listener.get());
    }


    FTEngine::cleanup();
}
