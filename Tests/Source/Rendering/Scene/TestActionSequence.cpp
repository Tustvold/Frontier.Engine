#include <Mock/MockLoader.h>
#include <Mock/MockAction.h>
#include <Rendering/Action/ActionSequence.h>
#include <Rendering/Director.h>
#include <Rendering/Node.h>
#include <Rendering/View.h>
#include <Rendering/Scene.h>

USING_NS_FT

TEST(TestActionSequence, TestSimple) {
    MockLoader loader;
    auto engine_event_dispatcher = loader.getMockEngineEventDispatcher();

    auto sequence = std::make_unique<ActionSequence>();
    auto mock1 = std::make_unique<MockAction>();
    auto mock1_ptr = mock1.get();
    auto mock2 = std::make_unique<MockAction>();
    auto mock2_ptr = mock2.get();
    auto node = std::make_shared<Node>();
    auto view = std::make_shared<View>();
    auto scene = std::make_shared<Scene>();
    scene->addView(view);
    Engine::getDirector()->setCurrentScene(scene, true);
    view->addChild(node);


    UpdateEvent update_event;

    EXPECT_CALL(*mock1_ptr, onStart(node.get())).WillOnce(testing::Invoke(mock1_ptr, &MockAction::callParentOnStart));

    sequence->addAction(std::move(mock1));
    sequence->addAction(std::move(mock2));
    node->runAction(std::move(sequence));

    testing::Mock::VerifyAndClearExpectations(mock1_ptr);

    testing::InSequence s;

    EXPECT_CALL(*mock1_ptr, onUpdate(node.get(), testing::_)).Times(3);
    EXPECT_CALL(*mock1_ptr, onUpdate(node.get(), testing::_)).WillOnce(testing::InvokeWithoutArgs(mock1_ptr, &MockAction::setCompleted));
    EXPECT_CALL(*mock2_ptr, onStart(node.get())).WillOnce(testing::Invoke(mock2_ptr, &MockAction::callParentOnStart));
    EXPECT_CALL(*mock2_ptr, onUpdate(node.get(), testing::_));

    engine_event_dispatcher->raiseEvent(update_event); // Update mock1
    engine_event_dispatcher->raiseEvent(update_event); // Update mock1
    engine_event_dispatcher->raiseEvent(update_event); // Update mock1
    engine_event_dispatcher->raiseEvent(update_event); // Update mock1 - mock1 marked finished - mock2 started - mock2 update called immediately

    testing::Mock::VerifyAndClearExpectations(mock1_ptr);
    testing::Mock::VerifyAndClearExpectations(mock2_ptr);

    EXPECT_CALL(*mock2_ptr, onUpdate(node.get(), testing::_)).Times(1);
    EXPECT_CALL(*mock2_ptr, onUpdate(node.get(), testing::_)).WillOnce(testing::InvokeWithoutArgs(mock2_ptr, &MockAction::setCompleted));
    EXPECT_CALL(*mock1_ptr, destroyed());
    EXPECT_CALL(*mock2_ptr, destroyed());

    engine_event_dispatcher->raiseEvent(update_event); // Update mock2
    engine_event_dispatcher->raiseEvent(update_event); // Update mock2 - mock2 marked finished - sequence marked finished and removed

}
