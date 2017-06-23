#pragma once

#include <Event/EventDispatcher.h>
#include <Event/Event.h>

NS_FT_BEGIN

class MockEvent1 : public Event {
};

class MockEvent2 : public Event {
};

class MockEventDispatcher : public EventDispatcher<MockEvent1> {
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

class MockEventDispatcher2 : public EventDispatcher<MockEvent1, MockEvent2> {
public:

    void sendMockEvent2() {
        MockEvent2 event;
        EventDispatcher<MockEvent2>::raiseEvent(event);
    }
};

class MockEventListener2 {
public:
    MOCK_METHOD1(callback, void(const MockEvent2&));
};

NS_FT_END