#include <glfwmock.h>
#include <FTEngine.h>
#include <Event/FTEventManager.h>
#include <Event/Mouse/FTMouseEventDispatcher.h>
#include <Rendering/FTNode.h>
#include <Rendering/FTButton.h>
#include <Rendering/FTView.h>
#include <Rendering/Camera/FTCamera2D.h>
#include <Rendering/FTScene.h>
#include <Rendering/FTDirector.h>
#include <Rendering/BoundingShape/FTBoundingCuboid.h>

class FTButton2DTestDelegates {
public:
    MOCK_METHOD1(enterDelegate, void(FTButton*));
    MOCK_METHOD1(exitDelegate, void(FTButton*));
    MOCK_METHOD1(selectDelegate, void(FTButton*));
    MOCK_METHOD1(deselectDelegate, void(FTButton*));
    MOCK_METHOD2(pressedDelegate, void(FTButton*, const FTMouseButtonPressedEvent&));
    MOCK_METHOD2(releasedDelegate, void(FTButton*, const FTMouseButtonReleasedEvent&));
    MOCK_METHOD1(enabledDelegate, bool(const FTButton*));
};

TEST(TestButton2D, TestContainsPosition) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
       

        auto node = std::make_shared<FTNode>();
        node->setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(100, 200, 0)));

        node->setPosition(glm::vec2(50, 60));

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(node);

        view->visit(glm::mat4(), false);

        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51, 61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149, 61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149, 259)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51, 259)));

        EXPECT_FALSE(node->containsMousePosition(glm::vec2(0, 0)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(151, 70)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(60, 261)));
    }

    FTEngine::cleanup();
}

TEST(TestButton2D, TestContainsPositionScale) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
        auto node = std::make_shared<FTNode>();
        node->setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(50, 50, 0)));
        node->setScale(glm::vec2(2, 4));
        node->setPosition(glm::vec2(50, 60));

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(node);

        auto scene = std::make_shared<FTScene>();
        scene->addView(view);
        FTEngine::getDirector()->setCurrentScene(scene, true);
        
        scene->visit();

        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51,61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149,61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149,259)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51,259)));

        EXPECT_FALSE(node->containsMousePosition(glm::vec2(0,0)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(151,70)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(60,261)));
    }

    FTEngine::cleanup();
}


TEST(TestButton2D, TestContainsPositionScaleAnchorPoint) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
        auto node = std::make_shared<FTNode>();

        node->setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(50, 50, 0)));
        node->setScale(glm::vec2(2, 4));
        node->setPosition(glm::vec2(100, 160));
        node->setAnchorPoint(glm::vec2(0.5f, 0.5f));

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(node);

        auto scene = std::make_shared<FTScene>();
        scene->addView(view);
        FTEngine::getDirector()->setCurrentScene(scene, true);

        scene->visit();

        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51,61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149,61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149,259)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51,259)));

        EXPECT_FALSE(node->containsMousePosition(glm::vec2(0,0)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(151,70)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(60,261)));
    }

    FTEngine::cleanup();
}

TEST(TestButton2D, TestEnterExitDelegates) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
        FTButton2DTestDelegates testDelegates;
        auto node = std::make_shared<FTNode>();

        node->setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(50, 50, 0)));
        node->setScale(glm::vec2(2, 4));
        node->setPosition(glm::vec2(100, 160));
        node->setAnchorPoint(glm::vec2(0.5f, 0.5f));
        auto& button = node->getButton();

        button->setUseSceneGraphPriority(false);
        button->bindMouseEnterDelegate(&testDelegates, &FTButton2DTestDelegates::enterDelegate);
        button->bindMouseExitDelegate(&testDelegates, &FTButton2DTestDelegates::exitDelegate);
        button->bindMousePressedDelegate(&testDelegates, &FTButton2DTestDelegates::pressedDelegate);
        button->bindMouseReleasedDelegate(&testDelegates, &FTButton2DTestDelegates::releasedDelegate);

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(node);

        auto scene = std::make_shared<FTScene>();
        scene->addView(view);
        FTEngine::getDirector()->setCurrentScene(scene, true);

        scene->visit();

        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51,61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149,61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149,259)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51,259)));

        EXPECT_FALSE(node->containsMousePosition(glm::vec2(0,0)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(151,70)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(60,261)));

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
        auto node = std::make_shared<FTNode>();

        node->setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(50, 50, 0)));
        node->setScale(glm::vec2(2, 4));
        node->setPosition(glm::vec2(100, 160));
        node->setAnchorPoint(glm::vec2(0.5f, 0.5f));

        auto& button = node->getButton();
        button->setUseSceneGraphPriority(false);
        button->bindMouseEnterDelegate(&testDelegates, &FTButton2DTestDelegates::enterDelegate);
        button->bindMouseExitDelegate(&testDelegates, &FTButton2DTestDelegates::exitDelegate);
        button->bindMousePressedDelegate(&testDelegates, &FTButton2DTestDelegates::pressedDelegate);
        button->bindMouseReleasedDelegate(&testDelegates, &FTButton2DTestDelegates::releasedDelegate);

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(node);

        auto scene = std::make_shared<FTScene>();
        scene->addView(view);
        FTEngine::getDirector()->setCurrentScene(scene, true);

        scene->visit();

        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51,61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149,61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149,259)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51,259)));

        EXPECT_FALSE(node->containsMousePosition(glm::vec2(0,0)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(151,70)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(60,261)));

        EXPECT_CALL(testDelegates, enterDelegate(button.get())).Times(0);
        
        auto screensize = FTEngine::getWindowSize();

        mock.mouse_pos_callback_(nullptr, 0, screensize.y - 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, pressedDelegate(button.get(), testing::_)).Times(0);

        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);

        EXPECT_CALL(testDelegates, enterDelegate(button.get()));
        mock.mouse_pos_callback_(nullptr, 51, screensize.y - 61);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, pressedDelegate(button.get(), testing::_));
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, releasedDelegate(button.get(), testing::_));
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, pressedDelegate(button.get(), testing::_));
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);
        
        EXPECT_CALL(testDelegates, enterDelegate(button.get())).Times(0);
        mock.mouse_pos_callback_(nullptr, 149, screensize.y - 61);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);



        EXPECT_CALL(testDelegates, exitDelegate(button.get()));
        mock.mouse_pos_callback_(nullptr, 0, screensize.y - 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, releasedDelegate(button.get(), testing::_)).Times(0);
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);

        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, exitDelegate(button.get())).Times(0);
        mock.mouse_pos_callback_(nullptr, 151, screensize.y - 70);
    }

    FTEngine::cleanup();
}

TEST(TestButton2D, TestDisconnectedDelegates) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
        auto node = std::make_shared<FTNode>();

        node->setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(50, 50, 0)));
        node->setScale(glm::vec2(2, 4));
        node->setPosition(glm::vec2(100, 160));
        node->setAnchorPoint(glm::vec2(0.5f, 0.5f));
        auto& button = node->getButton();

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(node);

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
        auto node = std::make_shared<FTNode>();

        node->setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(50, 50, 0)));
        node->setScale(glm::vec2(2, 4));
        node->setPosition(glm::vec2(100, 160));
        node->setAnchorPoint(glm::vec2(0.5f, 0.5f));
        auto& button = node->getButton();
        button->setUseSceneGraphPriority(false);
        button->bindEnabledDelegate(&testDelegates, &FTButton2DTestDelegates::enabledDelegate);

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(node);

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

TEST(TestButton2D, TestSelectDelegatesSimple) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
        FTButton2DTestDelegates testDelegates;
        auto node = std::make_shared<FTNode>();

        node->setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(50, 50, 0)));
        node->setScale(glm::vec2(2, 4));
        node->setPosition(glm::vec2(100, 160));
        node->setAnchorPoint(glm::vec2(0.5f, 0.5f));

        auto& button = node->getButton();
        button->setUseSceneGraphPriority(false);
        button->bindMousePressedDelegate(&testDelegates, &FTButton2DTestDelegates::pressedDelegate);
        button->bindOnSelectDelegate(&testDelegates, &FTButton2DTestDelegates::selectDelegate);
        button->bindOnDeselectDelegate(&testDelegates, &FTButton2DTestDelegates::deselectDelegate);
        button->bindMouseReleasedDelegate(&testDelegates, &FTButton2DTestDelegates::releasedDelegate);

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(node);

        auto scene = std::make_shared<FTScene>();
        scene->addView(view);
        FTEngine::getDirector()->setCurrentScene(scene, true);

        scene->visit();

        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51, 61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149, 61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149, 259)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51, 259)));

        EXPECT_FALSE(node->containsMousePosition(glm::vec2(0, 0)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(151, 70)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(60, 261)));

        auto screensize = FTEngine::getWindowSize();

        mock.mouse_pos_callback_(nullptr, 51, screensize.y - 61);

        
        EXPECT_CALL(testDelegates, pressedDelegate(button.get(), testing::_));
        EXPECT_CALL(testDelegates, selectDelegate(button.get()));

        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, releasedDelegate(button.get(), testing::_));
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);
        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, pressedDelegate(button.get(), testing::_));
        EXPECT_CALL(testDelegates, selectDelegate(button.get())).Times(0);

        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);

    }

    FTEngine::cleanup();
}

TEST(TestButton2D, TestDeselectDelegates) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
        FTButton2DTestDelegates testDelegates;

        auto node = std::make_shared<FTNode>();

        node->setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(50, 50, 0)));
        node->setScale(glm::vec2(2, 4));
        node->setPosition(glm::vec2(100, 160));
        node->setAnchorPoint(glm::vec2(0.5f, 0.5f));

        auto& button = node->getButton();
        button->setUseSceneGraphPriority(false);
        button->bindMousePressedDelegate(&testDelegates, &FTButton2DTestDelegates::pressedDelegate);
        button->bindOnSelectDelegate(&testDelegates, &FTButton2DTestDelegates::selectDelegate);
        button->bindOnDeselectDelegate(&testDelegates, &FTButton2DTestDelegates::deselectDelegate);
        button->bindMouseReleasedDelegate(&testDelegates, &FTButton2DTestDelegates::releasedDelegate);

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(node);

        auto scene = std::make_shared<FTScene>();
        scene->addView(view);
        FTEngine::getDirector()->setCurrentScene(scene, true);

        scene->visit();

        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51, 61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149, 61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149, 259)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51, 259)));

        EXPECT_FALSE(node->containsMousePosition(glm::vec2(0, 0)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(151, 70)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(60, 261)));

        auto screensize = FTEngine::getWindowSize();

        mock.mouse_pos_callback_(nullptr, 51, screensize.y - 61);


        EXPECT_CALL(testDelegates, pressedDelegate(button.get(), testing::_));
        EXPECT_CALL(testDelegates, selectDelegate(button.get()));

        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, releasedDelegate(button.get(), testing::_));
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);
        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, deselectDelegate(button.get()));

        mock.mouse_pos_callback_(nullptr, 0, 0);
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
    }

    FTEngine::cleanup();
}

TEST(TestButton2D, TestSelectMultiple) {
    GlfwMock mock;
    FTEngine::setup(true);
    {
        FTButton2DTestDelegates testDelegates;
        FTButton2DTestDelegates other_testDelegates;

        auto other_node = std::make_shared<FTNode>();
        other_node->setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(50, 50, 0)));

        auto node = std::make_shared<FTNode>();
        

        node->setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(50, 50, 0)));
        node->setScale(glm::vec2(2, 4));
        node->setPosition(glm::vec2(100, 160));
        node->setAnchorPoint(glm::vec2(0.5f, 0.5f));

        auto& button = node->getButton();
        button->setUseSceneGraphPriority(false);
        button->bindMousePressedDelegate(&testDelegates, &FTButton2DTestDelegates::pressedDelegate);
        button->bindOnSelectDelegate(&testDelegates, &FTButton2DTestDelegates::selectDelegate);
        button->bindOnDeselectDelegate(&testDelegates, &FTButton2DTestDelegates::deselectDelegate);
        button->bindMouseReleasedDelegate(&testDelegates, &FTButton2DTestDelegates::releasedDelegate);

        auto& other_button = other_node->getButton();
        other_button->setUseSceneGraphPriority(false);
        other_button->bindMousePressedDelegate(&other_testDelegates, &FTButton2DTestDelegates::pressedDelegate);
        other_button->bindOnSelectDelegate(&other_testDelegates, &FTButton2DTestDelegates::selectDelegate);
        other_button->bindOnDeselectDelegate(&other_testDelegates, &FTButton2DTestDelegates::deselectDelegate);
        other_button->bindMouseReleasedDelegate(&other_testDelegates, &FTButton2DTestDelegates::releasedDelegate);

        auto view = std::make_shared<FTView>();
        view->setCamera(std::make_shared<FTCamera2D>());
        view->addChild(node);
        view->addChild(other_node);

        auto scene = std::make_shared<FTScene>();
        scene->addView(view);
        FTEngine::getDirector()->setCurrentScene(scene, true);

        scene->visit();

        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51, 61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149, 61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149, 259)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51, 259)));

        EXPECT_FALSE(node->containsMousePosition(glm::vec2(0, 0)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(151, 70)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(60, 261)));

        auto screensize = FTEngine::getWindowSize();

        mock.mouse_pos_callback_(nullptr, 51, screensize.y - 61);


        EXPECT_CALL(testDelegates, pressedDelegate(button.get(), testing::_));
        EXPECT_CALL(testDelegates, selectDelegate(button.get()));

        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, releasedDelegate(button.get(), testing::_));
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);
        testing::Mock::VerifyAndClearExpectations(&testDelegates);

        EXPECT_CALL(testDelegates, deselectDelegate(button.get()));

        EXPECT_CALL(other_testDelegates, pressedDelegate(other_button.get(), testing::_));
        EXPECT_CALL(other_testDelegates, selectDelegate(other_button.get()));

        mock.mouse_pos_callback_(nullptr, 0, screensize.y - 0);
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
    }

    FTEngine::cleanup();
}