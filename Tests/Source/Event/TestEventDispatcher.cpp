#include <gmock/gmock.h>
#include "TestEventDispatcherTypes.h"

TEST(TestEventDispatcher, TestCallsDelegateSingle) {
    auto listener = new MockEventListener1();
    auto dispatcher = new MockEventDispatcher();

    EXPECT_CALL(*listener, callback(testing::_));

    auto delegate = Gallant::Delegate1<const MockEvent1&>(listener, &MockEventListener1::callback);
    dispatcher->registerDelegate(delegate);
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
    Gallant::Delegate1<const MockEvent1&> delegate1(listener, &MockEventListener1::callback);
    Gallant::Delegate1<const MockEvent2&> delegate2(listener2, &MockEventListener2::callback);

    dispatcher->registerDelegate(delegate1);
    dispatcher->registerDelegate(delegate2);

    dispatcher->sendMockEvent2();

    delete dispatcher;
    delete listener;
    delete listener2;
}
