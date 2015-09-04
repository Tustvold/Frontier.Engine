#include <Event/FTEventDispatcher.h>
#include <Event/FTEvent.h>
#include <gmock/gmock.h>

class MockEvent1 : public FTEvent {};
class MockEvent2 : public FTEvent {};

class MockEventDispatcher : public FTEventDispatcher<MockEvent1> {
public:
    void sendMockEvent1() {
        MockEvent1 event;
        this->raiseEvent(event);
    }
};

class MockEventListener1 {
public:
    MOCK_METHOD1(callback, void (const MockEvent1&));
};

class MockEventDispatcher2 : public FTEventDispatcher<MockEvent1,MockEvent2> {
public:

    void sendMockEvent2() {
        MockEvent2 event;
        FTEventDispatcher<MockEvent2>::raiseEvent(event);
    }
};

class MockEventListener2 {
public:
    MOCK_METHOD1(callback, void(const MockEvent2&));
};


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
