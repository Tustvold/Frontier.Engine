#include <Mock/MockLoader.h>
#include <Mock/MockAction.h>
#include <Rendering/Action/FTActionSequence.h>
#include <Rendering/FTDirector.h>
#include <Rendering/FTNode.h>
#include <Rendering/FTView.h>
#include <Rendering/FTScene.h>

TEST(TestActionSequence, TestSimple) {
    MockLoader loader;
    auto engine_event_dispatcher = loader.getMockEngineEventDispatcher();

    auto sequence = std::make_unique<FTActionSequence>();
    auto mock1 = std::make_unique<MockAction>();
    auto mock1_ptr = mock1.get();
    auto mock2 = std::make_unique<MockAction>();
    auto mock2_ptr = mock2.get();
    auto node = std::make_shared<FTNode>();
    auto view = std::make_shared<FTView>();
    auto scene = std::make_shared<FTScene>();
    scene->addView(view);
    FTEngine::getDirector()->setCurrentScene(scene);
    view->addChild(node);


    FTUpdateEvent update_event;

    EXPECT_CALL(*mock1_ptr, onStart(node.get())).WillOnce(testing::Invoke(mock1_ptr, &MockAction::callParentOnStart));

    sequence->addAction(std::move(mock1));
    sequence->addAction(std::move(mock2));
    node->runAction(std::move(sequence));

    testing::Mock::VerifyAndClearExpectations(mock1_ptr);

    testing::InSequence s;

    EXPECT_CALL(*mock1_ptr, onUpdate(node.get(), testing::_)).Times(3);
    EXPECT_CALL(*mock1_ptr, onUpdate(node.get(), testing::_)).WillOnce(testing::InvokeWithoutArgs(mock1_ptr, &MockAction::setCompleted));
    EXPECT_CALL(*mock2_ptr, onStart(node.get())).WillOnce(testing::Invoke(mock2_ptr, &MockAction::callParentOnStart));

    engine_event_dispatcher->raiseEvent(update_event); // Update mock1
    engine_event_dispatcher->raiseEvent(update_event); // Update mock1
    engine_event_dispatcher->raiseEvent(update_event); // Update mock1
    engine_event_dispatcher->raiseEvent(update_event); // Update mock1 - mock1 marked finished - mock2 started

    testing::Mock::VerifyAndClearExpectations(mock1_ptr);
    testing::Mock::VerifyAndClearExpectations(mock2_ptr);

    EXPECT_CALL(*mock2_ptr, onUpdate(node.get(), testing::_)).Times(1);
    EXPECT_CALL(*mock2_ptr, onUpdate(node.get(), testing::_)).WillOnce(testing::InvokeWithoutArgs(mock2_ptr, &MockAction::setCompleted));
    EXPECT_CALL(*mock1_ptr, destroyed());
    EXPECT_CALL(*mock2_ptr, destroyed());

    engine_event_dispatcher->raiseEvent(update_event); // Update mock2
    engine_event_dispatcher->raiseEvent(update_event); // Update mock2 - mock2 marked finished - sequence marked finished and removed

}
