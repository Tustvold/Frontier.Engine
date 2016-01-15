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
#include <Rendering/BoundingShape/FTBoundingCuboid.h>

class FTButton2DTestDelegates {
public:
    MOCK_METHOD1(enterDelegate, void(FTButton2D*));
    MOCK_METHOD1(exitDelegate, void(FTButton2D*));
    MOCK_METHOD1(pressedDelegate, void(FTButton2D*));
    MOCK_METHOD1(releasedDelegate, void(FTButton2D*));
    MOCK_METHOD1(enabledDelegate, bool(const FTButton2D*));
};

TEST(TestButton2D, TestContainsPosition) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
       

        auto renderer = std::make_shared<FTNode>();
        renderer->setBoundingShape(std::make_shared<FTBoundingCuboid>(glm::vec3(100, 200, 0)));

        renderer->setPosition(glm::vec2(50, 60));
        auto button = std::make_shared<FTButton2D>(std::move(renderer));

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(button);

        view->visit(glm::mat4(), false);

        EXPECT_TRUE(button->containsMousePosition(glm::vec2(51, 61)));
        EXPECT_TRUE(button->containsMousePosition(glm::vec2(149, 61)));
        EXPECT_TRUE(button->containsMousePosition(glm::vec2(149, 259)));
        EXPECT_TRUE(button->containsMousePosition(glm::vec2(51, 259)));

        EXPECT_FALSE(button->containsMousePosition(glm::vec2(0, 0)));
        EXPECT_FALSE(button->containsMousePosition(glm::vec2(151, 70)));
        EXPECT_FALSE(button->containsMousePosition(glm::vec2(60, 261)));
    }

    FTEngine::cleanup();
}

TEST(TestButton2D, TestContainsPositionScale) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
        auto renderer = std::make_shared<FTNode>();
        renderer->setBoundingShape(std::make_shared<FTBoundingCuboid>(glm::vec3(50, 50, 0)));
        renderer->setScale(glm::vec2(2, 4));
        renderer->setPosition(glm::vec2(50, 60));
        auto button = std::make_shared<FTButton2D>(std::move(renderer));

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(button);

        auto scene = std::make_shared<FTScene>();
        scene->addView(view);
        FTEngine::getDirector()->setCurrentScene(scene, true);
        
        scene->visit();

        EXPECT_TRUE(button->containsMousePosition(glm::vec2(51,61)));
        EXPECT_TRUE(button->containsMousePosition(glm::vec2(149,61)));
        EXPECT_TRUE(button->containsMousePosition(glm::vec2(149,259)));
        EXPECT_TRUE(button->containsMousePosition(glm::vec2(51,259)));

        EXPECT_FALSE(button->containsMousePosition(glm::vec2(0,0)));
        EXPECT_FALSE(button->containsMousePosition(glm::vec2(151,70)));
        EXPECT_FALSE(button->containsMousePosition(glm::vec2(60,261)));
    }

    FTEngine::cleanup();
}


TEST(TestButton2D, TestContainsPositionScaleAnchorPoint) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
        auto renderer = std::make_shared<FTNode>();

        renderer->setBoundingShape(std::make_shared<FTBoundingCuboid>(glm::vec3(50, 50, 0)));
        renderer->setScale(glm::vec2(2, 4));
        renderer->setPosition(glm::vec2(100, 160));
        renderer->setAnchorPoint(glm::vec2(0.5f, 0.5f));
        auto button = std::make_shared<FTButton2D>(std::move(renderer));

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(button);

        auto scene = std::make_shared<FTScene>();
        scene->addView(view);
        FTEngine::getDirector()->setCurrentScene(scene, true);

        scene->visit();

        EXPECT_TRUE(button->containsMousePosition(glm::vec2(51,61)));
        EXPECT_TRUE(button->containsMousePosition(glm::vec2(149,61)));
        EXPECT_TRUE(button->containsMousePosition(glm::vec2(149,259)));
        EXPECT_TRUE(button->containsMousePosition(glm::vec2(51,259)));

        EXPECT_FALSE(button->containsMousePosition(glm::vec2(0,0)));
        EXPECT_FALSE(button->containsMousePosition(glm::vec2(151,70)));
        EXPECT_FALSE(button->containsMousePosition(glm::vec2(60,261)));
    }

    FTEngine::cleanup();
}

TEST(TestButton2D, TestEnterExitDelegates) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
        FTButton2DTestDelegates testDelegates;
        auto renderer = std::make_shared<FTNode>();

        renderer->setBoundingShape(std::make_shared<FTBoundingCuboid>(glm::vec3(50, 50, 0)));
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
        FTEngine::getDirector()->setCurrentScene(scene, true);

        scene->visit();

        EXPECT_TRUE(button->containsMousePosition(glm::vec2(51,61)));
        EXPECT_TRUE(button->containsMousePosition(glm::vec2(149,61)));
        EXPECT_TRUE(button->containsMousePosition(glm::vec2(149,259)));
        EXPECT_TRUE(button->containsMousePosition(glm::vec2(51,259)));

        EXPECT_FALSE(button->containsMousePosition(glm::vec2(0,0)));
        EXPECT_FALSE(button->containsMousePosition(glm::vec2(151,70)));
        EXPECT_FALSE(button->containsMousePosition(glm::vec2(60,261)));

        EXPECT_CALL(testDelegates, enterDelegate(button.get())).Times(0);

        auto screensize = FTEngine::getWindowSize();

        mock.mouse_pos_callback_(nullptr, 0, screensize.y - 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, enterDelegate(button.get()));
        mock.mouse_pos_callback_(nullptr, 51, screensize.y - 61);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);
        
        EXPECT_CALL(testDelegates, enterDelegate(button.get())).Times(0);
        mock.mouse_pos_callback_(nullptr, 149, screensize.y - 61);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, exitDelegate(button.get()));
        mock.mouse_pos_callback_(nullptr, 0, screensize.y - 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, exitDelegate(button.get())).Times(0);
        mock.mouse_pos_callback_(nullptr, 151, screensize.y - 70);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, enterDelegate(button.get()));
        mock.mouse_pos_callback_(nullptr, 51, screensize.y - 61);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, exitDelegate(button.get()));
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

        renderer->setBoundingShape(std::make_shared<FTBoundingCuboid>(glm::vec3(50, 50, 0)));
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
        FTEngine::getDirector()->setCurrentScene(scene, true);

        scene->visit();

        EXPECT_TRUE(button->containsMousePosition(glm::vec2(51,61)));
        EXPECT_TRUE(button->containsMousePosition(glm::vec2(149,61)));
        EXPECT_TRUE(button->containsMousePosition(glm::vec2(149,259)));
        EXPECT_TRUE(button->containsMousePosition(glm::vec2(51,259)));

        EXPECT_FALSE(button->containsMousePosition(glm::vec2(0,0)));
        EXPECT_FALSE(button->containsMousePosition(glm::vec2(151,70)));
        EXPECT_FALSE(button->containsMousePosition(glm::vec2(60,261)));

        EXPECT_CALL(testDelegates, enterDelegate(button.get())).Times(0);
        
        auto screensize = FTEngine::getWindowSize();

        mock.mouse_pos_callback_(nullptr, 0, screensize.y - 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, pressedDelegate(button.get())).Times(0);

        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);

        EXPECT_CALL(testDelegates, enterDelegate(button.get()));
        mock.mouse_pos_callback_(nullptr, 51, screensize.y - 61);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, pressedDelegate(button.get()));
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, releasedDelegate(button.get()));
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, pressedDelegate(button.get()));
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);
        
        EXPECT_CALL(testDelegates, enterDelegate(button.get())).Times(0);
        mock.mouse_pos_callback_(nullptr, 149, screensize.y - 61);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);



        EXPECT_CALL(testDelegates, exitDelegate(button.get()));
        mock.mouse_pos_callback_(nullptr, 0, screensize.y - 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, releasedDelegate(button.get())).Times(0);
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, exitDelegate(button.get())).Times(0);
        mock.mouse_pos_callback_(nullptr, 151, screensize.y - 70);
    }

    FTEngine::cleanup();
}

TEST(TestButton2D, TestSizeScale) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
        auto renderer = std::make_shared<FTNode>();

        renderer->setBoundingShape(std::make_shared<FTBoundingCuboid>(glm::vec3(50, 50, 0)));
        renderer->setScale(glm::vec2(2, 4));
        renderer->setPosition(glm::vec2(100, 160));
        renderer->setAnchorPoint(glm::vec2(0.5f, 0.5f));
        auto button = std::make_shared<FTButton2D>(renderer);

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(button);

        auto scene = std::make_shared<FTScene>();
        scene->addView(view);
        FTEngine::getDirector()->setCurrentScene(scene, true);

        scene->visit();

        EXPECT_EQ(renderer->getBoundingShape()->getLayoutSize(), button->getBoundingShape()->getLayoutSize());
        EXPECT_EQ(renderer->getScale(), button->getScale());
    }

    FTEngine::cleanup();
}

TEST(TestButton2D, TestDisconnectedDelegates) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
        auto renderer = std::make_shared<FTNode>();

        renderer->setBoundingShape(std::make_shared<FTBoundingCuboid>(glm::vec3(50, 50, 0)));
        renderer->setScale(glm::vec2(2, 4));
        renderer->setPosition(glm::vec2(100, 160));
        renderer->setAnchorPoint(glm::vec2(0.5f, 0.5f));
        auto button = std::make_shared<FTButton2D>(renderer);

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(button);

        auto scene = std::make_shared<FTScene>();
        scene->addView(view);
        FTEngine::getDirector()->setCurrentScene(scene, true);

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


TEST(TestButton2D, TestEnabledDelegate) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
        FTButton2DTestDelegates testDelegates;
        auto renderer = std::make_shared<FTNode>();

        renderer->setBoundingShape(std::make_shared<FTBoundingCuboid>(glm::vec3(50, 50, 0)));
        renderer->setScale(glm::vec2(2, 4));
        renderer->setPosition(glm::vec2(100, 160));
        renderer->setAnchorPoint(glm::vec2(0.5f, 0.5f));
        auto button = std::make_shared<FTButton2D>(std::move(renderer));
        button->bindEnabledDelegate(&testDelegates, &FTButton2DTestDelegates::enabledDelegate);

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(button);

        testing::InSequence s;

        // This should fail as the node isn't added to the scene
        EXPECT_FALSE(button->getMouseDelegateEnabled());


        auto scene = std::make_shared<FTScene>();
        scene->addView(view);
        FTEngine::getDirector()->setCurrentScene(scene, true);
        
        EXPECT_CALL(testDelegates, enabledDelegate(button.get())).WillOnce(testing::Return(false));
        EXPECT_CALL(testDelegates, enabledDelegate(button.get())).WillOnce(testing::Return(true));

        EXPECT_FALSE(button->getMouseDelegateEnabled());
        EXPECT_TRUE(button->getMouseDelegateEnabled());
    }

    FTEngine::cleanup();
}