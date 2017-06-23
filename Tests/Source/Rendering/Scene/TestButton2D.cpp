#include <glfwmock.h>
#include <Engine.h>
#include <Event/EventManager.h>
#include <Event/Mouse/MouseEventDispatcher.h>
#include <Rendering/Node.h>
#include <Rendering/View.h>
#include <Rendering/Camera/Camera2D.h>
#include <Rendering/Scene.h>
#include <Rendering/Director.h>
#include <Rendering/BoundingShape/BoundingCuboid.h>
#include <gmock/gmock.h>

USING_NS_FT

class Button2DTestDelegates {
public:
    MOCK_METHOD1(enterDelegate, void(Button*));
    MOCK_METHOD1(exitDelegate, void(Button*));
    MOCK_METHOD1(selectDelegate, void(Button*));
    MOCK_METHOD1(deselectDelegate, void(Button*));
    MOCK_METHOD2(pressedDelegate, void(Button*, const MouseButtonPressedEvent&));
    MOCK_METHOD2(releasedDelegate, void(Button*, const MouseButtonReleasedEvent&));
    MOCK_METHOD1(enabledDelegate, bool(const Button*));
};

TEST(TestButton2D, TestContainsPosition) {
    GlfwMock mock;
    Engine::setup(true, true);
    {
       

        auto node = std::make_shared<Node>();
        node->setBoundingShape(std::make_unique<BoundingCuboid>(glm::vec3(100, 200, 0)));

        node->setPosition(glm::vec2(50, 60));

        auto view = std::make_shared<View>();
        view->setCamera(std::make_shared<Camera2D>());
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

    Engine::cleanup();
}

TEST(TestButton2D, TestContainsPositionScale) {
    GlfwMock mock;
    Engine::setup(true, true);
    {
        auto node = std::make_shared<Node>();
        node->setBoundingShape(std::make_unique<BoundingCuboid>(glm::vec3(50, 50, 0)));
        node->setScale(glm::vec2(2, 4));
        node->setPosition(glm::vec2(50, 60));

        auto view = std::make_shared<View>();
        view->setCamera(std::make_shared<Camera2D>());
        view->addChild(node);

        auto scene = std::make_shared<Scene>();
        scene->addView(view);
        Engine::getDirector()->setCurrentScene(scene, true);
        
        scene->visit();

        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51,61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149,61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149,259)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51,259)));

        EXPECT_FALSE(node->containsMousePosition(glm::vec2(0,0)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(151,70)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(60,261)));
    }

    Engine::cleanup();
}


TEST(TestButton2D, TestContainsPositionScaleAnchorPoint) {
    GlfwMock mock;
    Engine::setup(true, true);
    {
        auto node = std::make_shared<Node>();

        node->setBoundingShape(std::make_unique<BoundingCuboid>(glm::vec3(50, 50, 0)));
        node->setScale(glm::vec2(2, 4));
        node->setPosition(glm::vec2(100, 160));
        node->setAnchorPoint(glm::vec2(0.5f, 0.5f));

        auto view = std::make_shared<View>();
        view->setCamera(std::make_shared<Camera2D>());
        view->addChild(node);

        auto scene = std::make_shared<Scene>();
        scene->addView(view);
        Engine::getDirector()->setCurrentScene(scene, true);

        scene->visit();

        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51,61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149,61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149,259)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51,259)));

        EXPECT_FALSE(node->containsMousePosition(glm::vec2(0,0)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(151,70)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(60,261)));
    }

    Engine::cleanup();
}

TEST(TestButton2D, TestEnterExitDelegates) {
    GlfwMock mock;
    Engine::setup(true, true);
    {
        Button2DTestDelegates testDelegates;
        auto node = std::make_shared<Node>();

        node->setBoundingShape(std::make_unique<BoundingCuboid>(glm::vec3(50, 50, 0)));
        node->setScale(glm::vec2(2, 4));
        node->setPosition(glm::vec2(100, 160));
        node->setAnchorPoint(glm::vec2(0.5f, 0.5f));
        auto& button = node->getButton();

        button->setUseSceneGraphPriority(false);
        button->bindMouseEnterDelegate(&testDelegates, &Button2DTestDelegates::enterDelegate);
        button->bindMouseExitDelegate(&testDelegates, &Button2DTestDelegates::exitDelegate);
        button->bindMousePressedDelegate(&testDelegates, &Button2DTestDelegates::pressedDelegate);
        button->bindMouseReleasedDelegate(&testDelegates, &Button2DTestDelegates::releasedDelegate);

        auto view = std::make_shared<View>();
        view->setCamera(std::make_shared<Camera2D>());
        view->addChild(node);

        auto scene = std::make_shared<Scene>();
        scene->addView(view);
        Engine::getDirector()->setCurrentScene(scene, true);

        scene->visit();

        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51,61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149,61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149,259)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51,259)));

        EXPECT_FALSE(node->containsMousePosition(glm::vec2(0,0)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(151,70)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(60,261)));

        EXPECT_CALL(testDelegates, enterDelegate(button.get())).Times(0);

        auto screensize = Engine::getWindowSize();

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

    Engine::cleanup();
}

TEST(TestButton2D, TestPressDelegates) {
    GlfwMock mock;
    Engine::setup(true, true);
    {
        Button2DTestDelegates testDelegates;
        auto node = std::make_shared<Node>();

        node->setBoundingShape(std::make_unique<BoundingCuboid>(glm::vec3(50, 50, 0)));
        node->setScale(glm::vec2(2, 4));
        node->setPosition(glm::vec2(100, 160));
        node->setAnchorPoint(glm::vec2(0.5f, 0.5f));

        auto& button = node->getButton();
        button->setUseSceneGraphPriority(false);
        button->bindMouseEnterDelegate(&testDelegates, &Button2DTestDelegates::enterDelegate);
        button->bindMouseExitDelegate(&testDelegates, &Button2DTestDelegates::exitDelegate);
        button->bindMousePressedDelegate(&testDelegates, &Button2DTestDelegates::pressedDelegate);
        button->bindMouseReleasedDelegate(&testDelegates, &Button2DTestDelegates::releasedDelegate);

        auto view = std::make_shared<View>();
        view->setCamera(std::make_shared<Camera2D>());
        view->addChild(node);

        auto scene = std::make_shared<Scene>();
        scene->addView(view);
        Engine::getDirector()->setCurrentScene(scene, true);

        scene->visit();

        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51,61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149,61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149,259)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51,259)));

        EXPECT_FALSE(node->containsMousePosition(glm::vec2(0,0)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(151,70)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(60,261)));

        EXPECT_CALL(testDelegates, enterDelegate(button.get())).Times(0);
        
        auto screensize = Engine::getWindowSize();

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

    Engine::cleanup();
}

TEST(TestButton2D, TestDisconnectedDelegates) {
    GlfwMock mock;
    Engine::setup(true, true);
    {
        auto node = std::make_shared<Node>();

        node->setBoundingShape(std::make_unique<BoundingCuboid>(glm::vec3(50, 50, 0)));
        node->setScale(glm::vec2(2, 4));
        node->setPosition(glm::vec2(100, 160));
        node->setAnchorPoint(glm::vec2(0.5f, 0.5f));
        node->getButton();

        auto view = std::make_shared<View>();
        view->setCamera(std::make_shared<Camera2D>());
        view->addChild(node);

        auto scene = std::make_shared<Scene>();
        scene->addView(view);
        Engine::getDirector()->setCurrentScene(scene, true);

        scene->visit();

        auto screensize = Engine::getWindowSize();
        
        mock.mouse_pos_callback_(nullptr, 51, screensize.y - 61);
        mock.mouse_button_callback_(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
        mock.mouse_pos_callback_(nullptr, 0, screensize.y - 0);
        mock.mouse_pos_callback_(nullptr, 51, screensize.y - 61);
        mock.mouse_enter_callback_(nullptr, GL_FALSE);
    }

    Engine::cleanup();
}


TEST(TestButton2D, TestEnabledDelegate) {
    GlfwMock mock;
    Engine::setup(true, true);
    {
        Button2DTestDelegates testDelegates;
        auto node = std::make_shared<Node>();

        node->setBoundingShape(std::make_unique<BoundingCuboid>(glm::vec3(50, 50, 0)));
        node->setScale(glm::vec2(2, 4));
        node->setPosition(glm::vec2(100, 160));
        node->setAnchorPoint(glm::vec2(0.5f, 0.5f));
        auto& button = node->getButton();
        button->setUseSceneGraphPriority(false);
        button->bindEnabledDelegate(&testDelegates, &Button2DTestDelegates::enabledDelegate);

        auto view = std::make_shared<View>();
        view->setCamera(std::make_shared<Camera2D>());
        view->addChild(node);

        testing::InSequence s;

        // This should fail as the node isn't added to the scene
        EXPECT_FALSE(button->getMouseDelegateEnabled());


        auto scene = std::make_shared<Scene>();
        scene->addView(view);
        Engine::getDirector()->setCurrentScene(scene, true);
        
        EXPECT_CALL(testDelegates, enabledDelegate(button.get())).WillOnce(testing::Return(false));
        EXPECT_CALL(testDelegates, enabledDelegate(button.get())).WillOnce(testing::Return(true));

        EXPECT_FALSE(button->getMouseDelegateEnabled());
        EXPECT_TRUE(button->getMouseDelegateEnabled());
    }

    Engine::cleanup();
}

TEST(TestButton2D, TestSelectDelegatesSimple) {
    GlfwMock mock;
    Engine::setup(true, true);
    {
        Button2DTestDelegates testDelegates;
        auto node = std::make_shared<Node>();

        node->setBoundingShape(std::make_unique<BoundingCuboid>(glm::vec3(50, 50, 0)));
        node->setScale(glm::vec2(2, 4));
        node->setPosition(glm::vec2(100, 160));
        node->setAnchorPoint(glm::vec2(0.5f, 0.5f));

        auto& button = node->getButton();
        button->setUseSceneGraphPriority(false);
        button->bindMousePressedDelegate(&testDelegates, &Button2DTestDelegates::pressedDelegate);
        button->bindOnSelectDelegate(&testDelegates, &Button2DTestDelegates::selectDelegate);
        button->bindOnDeselectDelegate(&testDelegates, &Button2DTestDelegates::deselectDelegate);
        button->bindMouseReleasedDelegate(&testDelegates, &Button2DTestDelegates::releasedDelegate);

        auto view = std::make_shared<View>();
        view->setCamera(std::make_shared<Camera2D>());
        view->addChild(node);

        auto scene = std::make_shared<Scene>();
        scene->addView(view);
        Engine::getDirector()->setCurrentScene(scene, true);

        scene->visit();

        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51, 61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149, 61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149, 259)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51, 259)));

        EXPECT_FALSE(node->containsMousePosition(glm::vec2(0, 0)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(151, 70)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(60, 261)));

        auto screensize = Engine::getWindowSize();

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

    Engine::cleanup();
}

TEST(TestButton2D, TestDeselectDelegates) {
    GlfwMock mock;
    Engine::setup(true, true);
    {
        Button2DTestDelegates testDelegates;

        auto node = std::make_shared<Node>();

        node->setBoundingShape(std::make_unique<BoundingCuboid>(glm::vec3(50, 50, 0)));
        node->setScale(glm::vec2(2, 4));
        node->setPosition(glm::vec2(100, 160));
        node->setAnchorPoint(glm::vec2(0.5f, 0.5f));

        auto& button = node->getButton();
        button->setUseSceneGraphPriority(false);
        button->bindMousePressedDelegate(&testDelegates, &Button2DTestDelegates::pressedDelegate);
        button->bindOnSelectDelegate(&testDelegates, &Button2DTestDelegates::selectDelegate);
        button->bindOnDeselectDelegate(&testDelegates, &Button2DTestDelegates::deselectDelegate);
        button->bindMouseReleasedDelegate(&testDelegates, &Button2DTestDelegates::releasedDelegate);

        auto view = std::make_shared<View>();
        view->setCamera(std::make_shared<Camera2D>());
        view->addChild(node);

        auto scene = std::make_shared<Scene>();
        scene->addView(view);
        Engine::getDirector()->setCurrentScene(scene, true);

        scene->visit();

        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51, 61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149, 61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149, 259)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51, 259)));

        EXPECT_FALSE(node->containsMousePosition(glm::vec2(0, 0)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(151, 70)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(60, 261)));

        auto screensize = Engine::getWindowSize();

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

    Engine::cleanup();
}

TEST(TestButton2D, TestSelectMultiple) {
    GlfwMock mock;
    Engine::setup(true, true);
    {
        Button2DTestDelegates testDelegates;
        Button2DTestDelegates other_testDelegates;

        auto other_node = std::make_shared<Node>();
        other_node->setBoundingShape(std::make_unique<BoundingCuboid>(glm::vec3(50, 50, 0)));

        auto node = std::make_shared<Node>();
        

        node->setBoundingShape(std::make_unique<BoundingCuboid>(glm::vec3(50, 50, 0)));
        node->setScale(glm::vec2(2, 4));
        node->setPosition(glm::vec2(100, 160));
        node->setAnchorPoint(glm::vec2(0.5f, 0.5f));

        auto& button = node->getButton();
        button->setUseSceneGraphPriority(false);
        button->bindMousePressedDelegate(&testDelegates, &Button2DTestDelegates::pressedDelegate);
        button->bindOnSelectDelegate(&testDelegates, &Button2DTestDelegates::selectDelegate);
        button->bindOnDeselectDelegate(&testDelegates, &Button2DTestDelegates::deselectDelegate);
        button->bindMouseReleasedDelegate(&testDelegates, &Button2DTestDelegates::releasedDelegate);

        auto& other_button = other_node->getButton();
        other_button->setUseSceneGraphPriority(false);
        other_button->bindMousePressedDelegate(&other_testDelegates, &Button2DTestDelegates::pressedDelegate);
        other_button->bindOnSelectDelegate(&other_testDelegates, &Button2DTestDelegates::selectDelegate);
        other_button->bindOnDeselectDelegate(&other_testDelegates, &Button2DTestDelegates::deselectDelegate);
        other_button->bindMouseReleasedDelegate(&other_testDelegates, &Button2DTestDelegates::releasedDelegate);

        auto view = std::make_shared<View>();
        view->setCamera(std::make_shared<Camera2D>());
        view->addChild(node);
        view->addChild(other_node);

        auto scene = std::make_shared<Scene>();
        scene->addView(view);
        Engine::getDirector()->setCurrentScene(scene, true);

        scene->visit();

        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51, 61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149, 61)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(149, 259)));
        EXPECT_TRUE(node->containsMousePosition(glm::vec2(51, 259)));

        EXPECT_FALSE(node->containsMousePosition(glm::vec2(0, 0)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(151, 70)));
        EXPECT_FALSE(node->containsMousePosition(glm::vec2(60, 261)));

        auto screensize = Engine::getWindowSize();

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

    Engine::cleanup();
}