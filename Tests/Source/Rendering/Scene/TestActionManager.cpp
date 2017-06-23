#include <Mock/MockLoader.h>
#include <Rendering/Action/Action.h>
#include <Engine.h>
#include <Rendering/Node.h>
#include <Mock/MockEngineEventDispatcher.h>
#include <Rendering/Action/ActionManager.h>
#include <Rendering/Director.h>
#include <Rendering/Scene.h>
#include <Mock/MockAction.h>

USING_NS_FT

TEST(TestActionManager, TestAddRemove) {
    MockLoader loader;
   
    auto engine_event_dispatcher = loader.getMockEngineEventDispatcher();
    auto action_manager = Engine::getDirector()->getActionManager();
    auto node = std::make_shared<Node>();

    auto view = std::make_shared<View>();
    auto scene = std::make_shared<Scene>();
    auto empty_scene = std::make_shared<Scene>();
    scene->addView(view);
    view->addChild(node);

    auto action = std::make_unique<MockAction>();
    auto action_ptr = action.get();

    UpdateEvent updateEvent;

    EXPECT_CALL(*action_ptr, onStart(node.get())).Times(1);

    action_manager->addAction(node.get(), std::move(action));

    testing::Mock::VerifyAndClearExpectations(action_ptr);

    Engine::getDirector()->setCurrentScene(scene, true);

    EXPECT_CALL(*action_ptr, onUpdate(node.get(), updateEvent));

    engine_event_dispatcher->raiseEvent(updateEvent);

    testing::Mock::VerifyAndClearExpectations(action_ptr);

    Engine::getDirector()->setCurrentScene(empty_scene, true);

    // We don't expect the action to be run unless the node belongs to the hierarchy of the active scene
    EXPECT_CALL(*action_ptr, onUpdate(node.get(), updateEvent)).Times(0);

    engine_event_dispatcher->raiseEvent(updateEvent);

    testing::Mock::VerifyAndClearExpectations(action_ptr);

    Engine::getDirector()->setCurrentScene(scene, true);

    EXPECT_CALL(*action_ptr, onUpdate(node.get(), updateEvent));

    engine_event_dispatcher->raiseEvent(updateEvent);

    testing::Mock::VerifyAndClearExpectations(action_ptr);


    EXPECT_CALL(*action_ptr, onUpdate(node.get(), updateEvent)).Times(0);
    action_ptr->setPaused(true);


    engine_event_dispatcher->raiseEvent(updateEvent);

    testing::Mock::VerifyAndClearExpectations(action_ptr);


    EXPECT_CALL(*action_ptr, onUpdate(node.get(), updateEvent));
    action_ptr->setPaused(false);


    engine_event_dispatcher->raiseEvent(updateEvent);

    testing::Mock::VerifyAndClearExpectations(action_ptr);


    EXPECT_CALL(*action_ptr, onUpdate(node.get(), updateEvent)).Times(0);

    node->pauseAllActions();

    engine_event_dispatcher->raiseEvent(updateEvent);

    testing::Mock::VerifyAndClearExpectations(action_ptr);


    EXPECT_CALL(*action_ptr, onUpdate(node.get(), updateEvent));

    node->resumeAllActions();

    engine_event_dispatcher->raiseEvent(updateEvent);

    testing::Mock::VerifyAndClearExpectations(action_ptr);

    EXPECT_CALL(*action_ptr, onUpdate(node.get(), updateEvent)).Times(0);
    EXPECT_CALL(*action_ptr, destroyed());

    action_ptr->setCompleted();

    engine_event_dispatcher->raiseEvent(updateEvent);

    testing::Mock::VerifyAndClearExpectations(action_ptr);
}

TEST(TestActionManager, TestNoUpdate) {
    MockLoader loader;

    auto engine_event_dispatcher = loader.getMockEngineEventDispatcher();
    auto node = std::make_shared<Node>();

    auto view = std::make_shared<View>();
    auto scene = std::make_shared<Scene>();
    auto empty_scene = std::make_shared<Scene>();
    scene->addView(view);
    view->addChild(node);

    auto action = std::make_unique<MockAction>();
    auto action_ptr = action.get();

    UpdateEvent updateEvent;

    
    EXPECT_CALL(*action_ptr, onStart(node.get())).Times(1).WillOnce(testing::InvokeWithoutArgs(action_ptr, &MockAction::setCompleted));

    node->runAction(std::move(action));

    testing::Mock::VerifyAndClearExpectations(action_ptr);
    EXPECT_CALL(*action_ptr, onUpdate(testing::_, testing::_)).Times(0);
    EXPECT_CALL(*action_ptr, destroyed());

    engine_event_dispatcher->raiseEvent(updateEvent);
}
