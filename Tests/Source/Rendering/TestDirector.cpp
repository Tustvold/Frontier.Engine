#include <Mock/MockLoader.h>
#include <Rendering/FTScene.h>
#include <Rendering/FTDirector.h>

class MockSceneEnterExit : public FTScene {
public:
    MOCK_METHOD0(onEnter, void());
    MOCK_METHOD0(onExit, void());

    void callParentOnEnter() {
        FTScene::onEnter();
    }

    void callParentOnExit() {
        FTScene::onExit();
    }
};

class MockViewEnterExit : public FTView {
public:
    MOCK_METHOD0(onEnter, void());
    MOCK_METHOD0(onExit, void());

    void callParentOnEnter() {
        FTView::onEnter();
    }

    void callParentOnExit() {
        FTView::onExit();
    }
};

class MockNodeEnterExit : public FTNode {
public:
    MOCK_METHOD0(onEnter, void());
    MOCK_METHOD0(onExit, void());

    void callParentOnEnter() {
        FTNode::onEnter();
    }

    void callParentOnExit() {
        FTNode::onExit();
    }
};

TEST(TestDirector, TestEnterExit) {
    MockLoader loader;
    auto scene = std::make_shared<MockSceneEnterExit>();
    auto view = std::make_shared<MockViewEnterExit>();
    auto node1 = std::make_shared<MockNodeEnterExit>();
    auto node2 = std::make_shared<MockNodeEnterExit>();

    view->addChild(node1);
    
    

    FTEngine::getDirector()->setCurrentScene(scene);

    scene->addView(view);

    node1->addChild(node2);

    EXPECT_CALL(*scene, onEnter()).WillOnce(testing::Invoke(scene.get(), &MockSceneEnterExit::callParentOnEnter));
    EXPECT_CALL(*view, onEnter()).WillOnce(testing::Invoke(view.get(), &MockViewEnterExit::callParentOnEnter));
    EXPECT_CALL(*node1, onEnter()).WillOnce(testing::Invoke(node1.get(), &MockNodeEnterExit::callParentOnEnter));
    EXPECT_CALL(*node2, onEnter()).WillOnce(testing::Invoke(node2.get(), &MockNodeEnterExit::callParentOnEnter));

    loader.getMockEngineEventDispatcher()->raiseEvent(FTPreTickEvent());

    
    auto nextScene = std::make_shared<FTScene>();
    FTEngine::getDirector()->setCurrentScene(nextScene);

    EXPECT_CALL(*scene, onExit()).WillOnce(testing::Invoke(scene.get(), &MockSceneEnterExit::callParentOnExit));
    EXPECT_CALL(*view, onExit()).WillOnce(testing::Invoke(view.get(), &MockViewEnterExit::callParentOnExit));
    EXPECT_CALL(*node1, onExit()).WillOnce(testing::Invoke(node1.get(), &MockNodeEnterExit::callParentOnExit));
    EXPECT_CALL(*node2, onExit()).WillOnce(testing::Invoke(node2.get(), &MockNodeEnterExit::callParentOnExit));

    loader.getMockEngineEventDispatcher()->raiseEvent(FTPreTickEvent());

}

TEST(TestDirector, TestPushScene) {
    MockLoader loader;
    auto scene = std::make_shared<MockSceneEnterExit>();

    testing::InSequence s;



    FTEngine::getDirector()->setCurrentScene(scene);

    EXPECT_CALL(*scene, onEnter()).WillOnce(testing::Invoke(scene.get(), &MockSceneEnterExit::callParentOnEnter));

    loader.getMockEngineEventDispatcher()->raiseEvent(FTPreTickEvent());

    auto nextScene = std::make_shared<MockSceneEnterExit>();

    FTEngine::getDirector()->pushScene(nextScene);

    EXPECT_CALL(*scene, onExit()).WillOnce(testing::Invoke(scene.get(), &MockSceneEnterExit::callParentOnExit));
    EXPECT_CALL(*nextScene, onEnter()).WillOnce(testing::Invoke(nextScene.get(), &MockSceneEnterExit::callParentOnEnter));

    loader.getMockEngineEventDispatcher()->raiseEvent(FTPreTickEvent());



    
    FTEngine::getDirector()->popScene();

    EXPECT_CALL(*nextScene, onExit()).WillOnce(testing::Invoke(nextScene.get(), &MockSceneEnterExit::callParentOnExit));

    EXPECT_CALL(*scene, onEnter()).WillOnce(testing::Invoke(scene.get(), &MockSceneEnterExit::callParentOnEnter));

    loader.getMockEngineEventDispatcher()->raiseEvent(FTPreTickEvent());

    EXPECT_CALL(*scene, onExit()).WillOnce(testing::Invoke(scene.get(), &MockSceneEnterExit::callParentOnExit));
    // We expect a call when FTDirector is cleaned up
}