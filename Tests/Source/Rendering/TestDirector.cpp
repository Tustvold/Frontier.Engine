#include <Mock/MockLoader.h>
#include <Rendering/Scene.h>
#include <Rendering/Director.h>

USING_NS_FT

class MockSceneEnterExit : public Scene {
public:
    MOCK_METHOD0(onEnter, void());
    MOCK_METHOD0(onExit, void());

    void callParentOnEnter() {
        Scene::onEnter();
    }

    void callParentOnExit() {
        Scene::onExit();
    }
};

class MockViewEnterExit : public View {
public:
    MOCK_METHOD0(onEnter, void());
    MOCK_METHOD0(onExit, void());

    void callParentOnEnter() {
        View::onEnter();
    }

    void callParentOnExit() {
        View::onExit();
    }
};

class MockNodeEnterExit : public Node {
public:
    MOCK_METHOD0(onEnter, void());
    MOCK_METHOD0(onExit, void());

    void callParentOnEnter() {
        Node::onEnter();
    }

    void callParentOnExit() {
        Node::onExit();
    }
};

TEST(TestDirector, TestEnterExit) {
    MockLoader loader;
    auto scene = std::make_shared<MockSceneEnterExit>();
    auto view = std::make_shared<MockViewEnterExit>();
    auto node1 = std::make_shared<MockNodeEnterExit>();
    auto node2 = std::make_shared<MockNodeEnterExit>();

    view->addChild(node1);
    
    

    Engine::getDirector()->setCurrentScene(scene);

    scene->addView(view);

    node1->addChild(node2);

    EXPECT_CALL(*scene, onEnter()).WillOnce(testing::Invoke(scene.get(), &MockSceneEnterExit::callParentOnEnter));
    EXPECT_CALL(*view, onEnter()).WillOnce(testing::Invoke(view.get(), &MockViewEnterExit::callParentOnEnter));
    EXPECT_CALL(*node1, onEnter()).WillOnce(testing::Invoke(node1.get(), &MockNodeEnterExit::callParentOnEnter));
    EXPECT_CALL(*node2, onEnter()).WillOnce(testing::Invoke(node2.get(), &MockNodeEnterExit::callParentOnEnter));

    loader.getMockEngineEventDispatcher()->raiseEvent(PreTickEvent());

    
    auto nextScene = std::make_shared<Scene>();
    Engine::getDirector()->setCurrentScene(nextScene);

    EXPECT_CALL(*scene, onExit()).WillOnce(testing::Invoke(scene.get(), &MockSceneEnterExit::callParentOnExit));
    EXPECT_CALL(*view, onExit()).WillOnce(testing::Invoke(view.get(), &MockViewEnterExit::callParentOnExit));
    EXPECT_CALL(*node1, onExit()).WillOnce(testing::Invoke(node1.get(), &MockNodeEnterExit::callParentOnExit));
    EXPECT_CALL(*node2, onExit()).WillOnce(testing::Invoke(node2.get(), &MockNodeEnterExit::callParentOnExit));

    loader.getMockEngineEventDispatcher()->raiseEvent(PreTickEvent());

}

TEST(TestDirector, TestPushScene) {
    MockLoader loader;
    auto scene = std::make_shared<MockSceneEnterExit>();

    testing::InSequence s;



    Engine::getDirector()->setCurrentScene(scene);

    EXPECT_CALL(*scene, onEnter()).WillOnce(testing::Invoke(scene.get(), &MockSceneEnterExit::callParentOnEnter));

    loader.getMockEngineEventDispatcher()->raiseEvent(PreTickEvent());

    auto nextScene = std::make_shared<MockSceneEnterExit>();

    Engine::getDirector()->pushScene(nextScene);

    EXPECT_CALL(*scene, onExit()).WillOnce(testing::Invoke(scene.get(), &MockSceneEnterExit::callParentOnExit));
    EXPECT_CALL(*nextScene, onEnter()).WillOnce(testing::Invoke(nextScene.get(), &MockSceneEnterExit::callParentOnEnter));

    loader.getMockEngineEventDispatcher()->raiseEvent(PreTickEvent());



    
    Engine::getDirector()->popScene();

    EXPECT_CALL(*nextScene, onExit()).WillOnce(testing::Invoke(nextScene.get(), &MockSceneEnterExit::callParentOnExit));

    EXPECT_CALL(*scene, onEnter()).WillOnce(testing::Invoke(scene.get(), &MockSceneEnterExit::callParentOnEnter));

    loader.getMockEngineEventDispatcher()->raiseEvent(PreTickEvent());

    EXPECT_CALL(*scene, onExit()).WillOnce(testing::Invoke(scene.get(), &MockSceneEnterExit::callParentOnExit));
    // We expect a call when Director is cleaned up
}