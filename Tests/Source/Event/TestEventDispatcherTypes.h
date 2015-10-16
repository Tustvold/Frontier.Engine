#pragma once

#include <Event/FTEventDispatcher.h>
#include <Event/FTEvent.h>

class MockEvent1 : public FTEvent {
};

class MockEvent2 : public FTEvent {
};

class MockEventDispatcher : public FTEventDispatcher<MockEvent1> {
public:
    void sendMockEvent1() {
        MockEvent1 event;
        this->raiseEvent(event);
    }
};

class MockEventListener1 {
public:
    MOCK_METHOD1(callback, void(const MockEvent1&));
};

class MockEventDispatcher2 : public FTEventDispatcher<MockEvent1, MockEvent2> {
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
