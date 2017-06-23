#include <gmock/gmock.h>
#include "TestEventDispatcherTypes.h"

USING_NS_FT

TEST(TestEventDispatcher, TestCallsDelegateSingle) {
    auto listener = new MockEventListener1();
    auto dispatcher = new MockEventDispatcher();

    EXPECT_CALL(*listener, callback(testing::_));

    dispatcher->registerDelegate(listener, &MockEventListener1::callback);
    dispatcher->sendMockEvent1();

    delete dispatcher;
    delete listener;
}

TEST(TestEventDispatcher, TestCallsDelegateDouble) {
    auto listener = new MockEventListener1();
    auto listener2 = new MockEventListener2();
    auto dispatcher = new MockEventDispatcher2();

    EXPECT_CALL(*listener2, callback(testing::_));
    EXPECT_CALL(*listener, callback(testing::_)).Times(0);

    dispatcher->registerDelegate(listener, &MockEventListener1::callback);
    dispatcher->registerDelegate(listener2, &MockEventListener2::callback);

    dispatcher->sendMockEvent2();

    delete dispatcher;
    delete listener;
    delete listener2;
}

TEST(TestEventDispatcher, TestUnregister) {
    auto listener = new MockEventListener1();
    auto dispatcher = new MockEventDispatcher();

    testing::InSequence s;

    EXPECT_CALL(*listener, callback(testing::_));


    dispatcher->registerDelegate(listener, &MockEventListener1::callback);
    dispatcher->sendMockEvent1();

    EXPECT_CALL(*listener, callback(testing::_)).Times(0);

    dispatcher->unregisterDelegate(listener, &MockEventListener1::callback);
    dispatcher->sendMockEvent1();

    delete dispatcher;
    delete listener;
}
