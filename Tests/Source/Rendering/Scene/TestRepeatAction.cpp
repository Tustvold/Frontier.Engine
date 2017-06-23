#include <Mock/MockLoader.h>
#include <Mock/MockAction.h>
#include <Rendering/View.h>
#include <Rendering/Scene.h>
#include <Rendering/Director.h>
#include <Rendering/Action/RepeatAction.h>

USING_NS_FT

TEST(TestRepeatAction, TestSimple) {
    MockLoader loader;
    auto engine_event_dispatcher = loader.getMockEngineEventDispatcher();

    auto mock1 = std::make_unique<MockAction>();
    auto mock1_ptr = mock1.get();

    auto repeat = std::make_unique<RepeatAction>(std::move(mock1), 2);

    auto node = std::make_shared<Node>();
    auto view = std::make_shared<View>();
    auto scene = std::make_shared<Scene>();
    scene->addView(view);
    Engine::getDirector()->setCurrentScene(scene, true);
    view->addChild(node);

    UpdateEvent update_event;

    EXPECT_CALL(*mock1_ptr, onStart(node.get())).WillOnce(testing::Invoke(mock1_ptr, &MockAction::callParentOnStart));
    node->runAction(std::move(repeat));

    testing::Mock::VerifyAndClearExpectations(mock1_ptr);

    testing::InSequence s;

    EXPECT_CALL(*mock1_ptr, onUpdate(node.get(), testing::_)).Times(3);
    EXPECT_CALL(*mock1_ptr, onUpdate(node.get(), testing::_)).WillOnce(testing::InvokeWithoutArgs(mock1_ptr, &MockAction::setCompleted));
    EXPECT_CALL(*mock1_ptr, onStart(node.get())).WillOnce(testing::Invoke(mock1_ptr, &MockAction::callParentOnStart));
    
    engine_event_dispatcher->raiseEvent(update_event); // Update mock1
    engine_event_dispatcher->raiseEvent(update_event); // Update mock1
    engine_event_dispatcher->raiseEvent(update_event); // Update mock1
    engine_event_dispatcher->raiseEvent(update_event); // Update mock1 - mock1 set completed - repeat action schedules repeat

    testing::Mock::VerifyAndClearExpectations(mock1_ptr);

    EXPECT_CALL(*mock1_ptr, onUpdate(testing::_, testing::_)).Times(2);
    
    engine_event_dispatcher->raiseEvent(update_event); // Update mock1
    engine_event_dispatcher->raiseEvent(update_event); // Update mock1

    testing::Mock::VerifyAndClearExpectations(mock1_ptr);

    EXPECT_CALL(*mock1_ptr, onUpdate(testing::_, testing::_)).Times(0);
    EXPECT_CALL(*mock1_ptr, destroyed());

    // Setting the action to be completed outside onUpdate should remove the event at the next update and onUpdate should not be called
    mock1_ptr->setCompleted();
    
    engine_event_dispatcher->raiseEvent(update_event);
}

TEST(TestRepeatAction, TestNested) {
    MockLoader loader;
    auto engine_event_dispatcher = loader.getMockEngineEventDispatcher();

    auto mock1 = std::make_unique<MockAction>();
    auto mock1_ptr = mock1.get();

    auto repeat = std::make_unique<RepeatAction>(std::move(mock1), 2);
    auto repeat_parent = std::make_unique<RepeatAction>(std::move(repeat), 3);

    auto node = std::make_shared<Node>();
    auto view = std::make_shared<View>();
    auto scene = std::make_shared<Scene>();
    scene->addView(view);
    Engine::getDirector()->setCurrentScene(scene, true);
    view->addChild(node);

    UpdateEvent update_event;

    testing::InSequence s;

    EXPECT_CALL(*mock1_ptr, onStart(node.get())).WillOnce(testing::Invoke(mock1_ptr, &MockAction::callParentOnStart));
    node->runAction(std::move(repeat_parent));

    testing::Mock::VerifyAndClearExpectations(mock1_ptr);
    EXPECT_CALL(*mock1_ptr, onUpdate(node.get(), testing::_)).Times(1);
    EXPECT_CALL(*mock1_ptr, onUpdate(node.get(), testing::_)).WillOnce(testing::InvokeWithoutArgs(mock1_ptr, &MockAction::setCompleted));
    EXPECT_CALL(*mock1_ptr, onStart(node.get())).WillOnce(testing::Invoke(mock1_ptr, &MockAction::callParentOnStart));
    
    EXPECT_CALL(*mock1_ptr, onUpdate(node.get(), testing::_)).Times(1);
    EXPECT_CALL(*mock1_ptr, onUpdate(node.get(), testing::_)).WillOnce(testing::InvokeWithoutArgs(mock1_ptr, &MockAction::setCompleted));
    EXPECT_CALL(*mock1_ptr, onStart(node.get())).WillOnce(testing::Invoke(mock1_ptr, &MockAction::callParentOnStart));

    EXPECT_CALL(*mock1_ptr, onUpdate(node.get(), testing::_)).WillOnce(testing::InvokeWithoutArgs(mock1_ptr, &MockAction::setCompleted));
    EXPECT_CALL(*mock1_ptr, onStart(node.get())).WillOnce(testing::Invoke(mock1_ptr, &MockAction::callParentOnStart));

    EXPECT_CALL(*mock1_ptr, onUpdate(node.get(), testing::_)).WillOnce(testing::InvokeWithoutArgs(mock1_ptr, &MockAction::setCompleted));
    EXPECT_CALL(*mock1_ptr, onStart(node.get())).WillOnce(testing::Invoke(mock1_ptr, &MockAction::callParentOnStart));

    EXPECT_CALL(*mock1_ptr, onUpdate(node.get(), testing::_)).Times(1);
    EXPECT_CALL(*mock1_ptr, onUpdate(node.get(), testing::_)).WillOnce(testing::InvokeWithoutArgs(mock1_ptr, &MockAction::setCompleted));
    EXPECT_CALL(*mock1_ptr, onStart(node.get())).WillOnce(testing::Invoke(mock1_ptr, &MockAction::callParentOnStart));
    
    EXPECT_CALL(*mock1_ptr, onUpdate(node.get(), testing::_)).WillOnce(testing::InvokeWithoutArgs(mock1_ptr, &MockAction::setCompleted));
    EXPECT_CALL(*mock1_ptr, destroyed());

    engine_event_dispatcher->raiseEvent(update_event); // Update mock1
    engine_event_dispatcher->raiseEvent(update_event); // Update mock1 - mark mock1 completed - onStart called on mock1

    engine_event_dispatcher->raiseEvent(update_event); // Update mock1
    engine_event_dispatcher->raiseEvent(update_event); // Update mock1 - mark mock1 completed - repeat marked completed - onStart called on repeat - onStart called on mock1

    engine_event_dispatcher->raiseEvent(update_event); // Update mock1 - mark mock1 completed - onStart called on mock1

    engine_event_dispatcher->raiseEvent(update_event); // Update mock1 - mark mock1 completed - repeat marked completed - onStart called on repeat - onStart called on mock1

    engine_event_dispatcher->raiseEvent(update_event); // Update mock1
    engine_event_dispatcher->raiseEvent(update_event); // Update mock1 - mark mock1 completed - onStart called on mock1

    engine_event_dispatcher->raiseEvent(update_event); // Update mock1 - mark mock1 completed - repeat marked completed - repeat_parent marked completed - actions destroyed
    
}
