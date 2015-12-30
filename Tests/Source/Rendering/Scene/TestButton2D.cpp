#include <glfwmock.h>
#include <FTEngine.h>
#include <Event/FTEventManager.h>
#include <Event/Mouse/FTMouseEventDispatcher.h>
#include <Rendering/FTNode.h>
#include <Rendering/FTButton2D.h>
#include <Rendering/FTView.h>
#include <Rendering/Camera/FTCamera2D.h>
#include <Rendering/FTScene.h>
#include <Rendering/FTDirector.h>

class FTButton2DTestDelegates {
public:
    MOCK_METHOD0(enterDelegate, void());
    MOCK_METHOD0(exitDelegate, void());
    MOCK_METHOD0(pressedDelegate, void());
    MOCK_METHOD0(releasedDelegate, void());
};

TEST(TestButton2D, TestContainsPosition) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
       

        auto renderer = std::make_shared<FTNode>();
        renderer->setSize(glm::vec2(100, 200));
        renderer->setPosition(glm::vec2(50, 60));
        auto button = std::make_shared<FTButton2D>(std::move(renderer));

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(button);

        view->visit(glm::mat4(), false);

        EXPECT_TRUE(button->rendererContainsMousePoint(51, 61));
        EXPECT_TRUE(button->rendererContainsMousePoint(149, 61));
        EXPECT_TRUE(button->rendererContainsMousePoint(149, 259));
        EXPECT_TRUE(button->rendererContainsMousePoint(51, 259));

        EXPECT_FALSE(button->rendererContainsMousePoint(0, 0));
        EXPECT_FALSE(button->rendererContainsMousePoint(151, 70));
        EXPECT_FALSE(button->rendererContainsMousePoint(60, 261));
    }

    FTEngine::cleanup();
}

TEST(TestButton2D, TestContainsPositionScale) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
        auto renderer = std::make_shared<FTNode>();

        renderer->setSize(glm::vec2(50, 50));
        renderer->setScale(glm::vec2(2, 4));
        renderer->setPosition(glm::vec2(50, 60));
        auto button = std::make_shared<FTButton2D>(std::move(renderer));

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(button);

        auto scene = std::make_shared<FTScene>();
        scene->addView(view);
        FTEngine::getDirector()->setCurrentScene(scene);
        
        scene->visit();

        EXPECT_TRUE(button->rendererContainsMousePoint(51, 61));
        EXPECT_TRUE(button->rendererContainsMousePoint(149, 61));
        EXPECT_TRUE(button->rendererContainsMousePoint(149, 259));
        EXPECT_TRUE(button->rendererContainsMousePoint(51, 259));

        EXPECT_FALSE(button->rendererContainsMousePoint(0, 0));
        EXPECT_FALSE(button->rendererContainsMousePoint(151, 70));
        EXPECT_FALSE(button->rendererContainsMousePoint(60, 261));
    }

    FTEngine::cleanup();
}


TEST(TestButton2D, TestContainsPositionScaleAnchorPoint) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
        auto renderer = std::make_shared<FTNode>();

        renderer->setSize(glm::vec2(50, 50));
        renderer->setScale(glm::vec2(2, 4));
        renderer->setPosition(glm::vec2(100, 160));
        renderer->setAnchorPoint(glm::vec2(0.5f, 0.5f));
        auto button = std::make_shared<FTButton2D>(std::move(renderer));

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(button);

        auto scene = std::make_shared<FTScene>();
        scene->addView(view);
        FTEngine::getDirector()->setCurrentScene(scene);

        scene->visit();

        EXPECT_TRUE(button->rendererContainsMousePoint(51, 61));
        EXPECT_TRUE(button->rendererContainsMousePoint(149, 61));
        EXPECT_TRUE(button->rendererContainsMousePoint(149, 259));
        EXPECT_TRUE(button->rendererContainsMousePoint(51, 259));

        EXPECT_FALSE(button->rendererContainsMousePoint(0, 0));
        EXPECT_FALSE(button->rendererContainsMousePoint(151, 70));
        EXPECT_FALSE(button->rendererContainsMousePoint(60, 261));
    }

    FTEngine::cleanup();
}

TEST(TestButton2D, TestEnterExitDelegates) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
        FTButton2DTestDelegates testDelegates;
        auto renderer = std::make_shared<FTNode>();

        renderer->setSize(glm::vec2(50, 50));
        renderer->setScale(glm::vec2(2, 4));
        renderer->setPosition(glm::vec2(100, 160));
        renderer->setAnchorPoint(glm::vec2(0.5f, 0.5f));
        auto button = std::make_shared<FTButton2D>(std::move(renderer));
        button->bindMouseEnterDelegate(&testDelegates, &FTButton2DTestDelegates::enterDelegate);
        button->bindMouseExitDelegate(&testDelegates, &FTButton2DTestDelegates::exitDelegate);
        button->bindMousePressedDelegate(&testDelegates, &FTButton2DTestDelegates::pressedDelegate);
        button->bindMouseReleasedDelegate(&testDelegates, &FTButton2DTestDelegates::releasedDelegate);

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(button);

        auto scene = std::make_shared<FTScene>();
        scene->addView(view);
        FTEngine::getDirector()->setCurrentScene(scene);

        scene->visit();

        EXPECT_TRUE(button->rendererContainsMousePoint(51, 61));
        EXPECT_TRUE(button->rendererContainsMousePoint(149, 61));
        EXPECT_TRUE(button->rendererContainsMousePoint(149, 259));
        EXPECT_TRUE(button->rendererContainsMousePoint(51, 259));

        EXPECT_FALSE(button->rendererContainsMousePoint(0, 0));
        EXPECT_FALSE(button->rendererContainsMousePoint(151, 70));
        EXPECT_FALSE(button->rendererContainsMousePoint(60, 261));

        EXPECT_CALL(testDelegates, enterDelegate()).Times(0);

        auto screensize = FTEngine::getWindowSize();

        mock.mouse_pos_callback_(nullptr, 0, screensize.y - 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, enterDelegate());
        mock.mouse_pos_callback_(nullptr, 51, screensize.y - 61);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);
        
        EXPECT_CALL(testDelegates, enterDelegate()).Times(0);
        mock.mouse_pos_callback_(nullptr, 149, screensize.y - 61);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, exitDelegate());
        mock.mouse_pos_callback_(nullptr, 0, screensize.y - 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, exitDelegate()).Times(0);
        mock.mouse_pos_callback_(nullptr, 151, screensize.y - 70);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, enterDelegate());
        mock.mouse_pos_callback_(nullptr, 51, screensize.y - 61);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, exitDelegate());
        mock.mouse_enter_callback_(nullptr, GL_FALSE);
    }

    FTEngine::cleanup();
}

TEST(TestButton2D, TestPressDelegates) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
        FTButton2DTestDelegates testDelegates;
        auto renderer = std::make_shared<FTNode>();

        renderer->setSize(glm::vec2(50, 50));
        renderer->setScale(glm::vec2(2, 4));
        renderer->setPosition(glm::vec2(100, 160));
        renderer->setAnchorPoint(glm::vec2(0.5f, 0.5f));
        auto button = std::make_shared<FTButton2D>(std::move(renderer));
        button->bindMouseEnterDelegate(&testDelegates, &FTButton2DTestDelegates::enterDelegate);
        button->bindMouseExitDelegate(&testDelegates, &FTButton2DTestDelegates::exitDelegate);
        button->bindMousePressedDelegate(&testDelegates, &FTButton2DTestDelegates::pressedDelegate);
        button->bindMouseReleasedDelegate(&testDelegates, &FTButton2DTestDelegates::releasedDelegate);

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(button);

        auto scene = std::make_shared<FTScene>();
        scene->addView(view);
        FTEngine::getDirector()->setCurrentScene(scene);

        scene->visit();

        EXPECT_TRUE(button->rendererContainsMousePoint(51, 61));
        EXPECT_TRUE(button->rendererContainsMousePoint(149, 61));
        EXPECT_TRUE(button->rendererContainsMousePoint(149, 259));
        EXPECT_TRUE(button->rendererContainsMousePoint(51, 259));

        EXPECT_FALSE(button->rendererContainsMousePoint(0, 0));
        EXPECT_FALSE(button->rendererContainsMousePoint(151, 70));
        EXPECT_FALSE(button->rendererContainsMousePoint(60, 261));

        EXPECT_CALL(testDelegates, enterDelegate()).Times(0);
        
        auto screensize = FTEngine::getWindowSize();

        mock.mouse_pos_callback_(nullptr, 0, screensize.y - 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, pressedDelegate()).Times(0);

        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);

        EXPECT_CALL(testDelegates, enterDelegate());
        mock.mouse_pos_callback_(nullptr, 51, screensize.y - 61);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, pressedDelegate());
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, releasedDelegate());
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, pressedDelegate());
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);
        
        EXPECT_CALL(testDelegates, enterDelegate()).Times(0);
        mock.mouse_pos_callback_(nullptr, 149, screensize.y - 61);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);



        EXPECT_CALL(testDelegates, exitDelegate());
        mock.mouse_pos_callback_(nullptr, 0, screensize.y - 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, releasedDelegate()).Times(0);
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, exitDelegate()).Times(0);
        mock.mouse_pos_callback_(nullptr, 151, screensize.y - 70);
    }

    FTEngine::cleanup();
}

TEST(TestButton2D, TestSizeScale) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
        auto renderer = std::make_shared<FTNode>();

        renderer->setSize(glm::vec2(50, 50));
        renderer->setScale(glm::vec2(2, 4));
        renderer->setPosition(glm::vec2(100, 160));
        renderer->setAnchorPoint(glm::vec2(0.5f, 0.5f));
        auto button = std::make_shared<FTButton2D>(renderer);

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(button);

        auto scene = std::make_shared<FTScene>();
        scene->addView(view);
        FTEngine::getDirector()->setCurrentScene(scene);

        scene->visit();

        EXPECT_EQ(renderer->getSize(), button->getSize());
        EXPECT_EQ(renderer->getScale(), button->getScale());
    }

    FTEngine::cleanup();
}

TEST(TestButton2D, TestDisconnectedDelegates) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
        auto renderer = std::make_shared<FTNode>();

        renderer->setSize(glm::vec2(50, 50));
        renderer->setScale(glm::vec2(2, 4));
        renderer->setPosition(glm::vec2(100, 160));
        renderer->setAnchorPoint(glm::vec2(0.5f, 0.5f));
        auto button = std::make_shared<FTButton2D>(renderer);

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(button);

        auto scene = std::make_shared<FTScene>();
        scene->addView(view);
        FTEngine::getDirector()->setCurrentScene(scene);

        scene->visit();

        auto screensize = FTEngine::getWindowSize();
        
        mock.mouse_pos_callback_(nullptr, 51, screensize.y - 61);
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
        mock.mouse_pos_callback_(nullptr, 0, screensize.y - 0);
        mock.mouse_pos_callback_(nullptr, 51, screensize.y - 61);
        mock.mouse_enter_callback_(nullptr, GL_FALSE);
    }

    FTEngine::cleanup();
}