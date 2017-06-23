#pragma once

#include "Event.h"
#include "EventHelpers.h"

NS_FT_BEGIN

class EventDispatcherBase {
public:
    virtual ~EventDispatcherBase() {
    }
};

// Base template declaration
template <typename... EventType>
class EventDispatcher {
};

// Sentinel template specialization
template <>
class EventDispatcher<> : public EventDispatcherBase {
public:
    virtual ~EventDispatcher() {

    }
};

// Recursive template specialization
template <typename EventType, typename... Others>
class EventDispatcher<EventType, Others...> : public EventDispatcher<Others...>, public details::SignalManager<EventType> {
public:
    static_assert(std::is_base_of<Event, EventType>::value, "Event is not derived from Event");

    virtual ~EventDispatcher() {

    }

    template <typename T>
    void registerDelegate(const Gallant::Delegate1<const T&>& delegate) {
        details::SignalSelector<T, EventType, Others...> selector;
        auto manager = (details::SignalManager<T>*)this;
        auto& eventHandler = selector.getEventHandler(manager);
        eventHandler.Connect(delegate);
    }

    template <typename T, typename X, typename Y>
    void registerDelegate(Y* obj, void (X::*func)(const T& p1)) {
        registerDelegate(Gallant::MakeDelegate(obj, func));
    }

    template <typename T>
    void unregisterDelegate(const Gallant::Delegate1<const T&>& delegate) {
        details::SignalSelector<T, EventType, Others...> selector;
        auto manager = (details::SignalManager<T>*)this;
        auto& eventHandler = selector.getEventHandler(manager);
        eventHandler.Disconnect(delegate);
    }

    template <typename T, typename X, typename Y>
    void unregisterDelegate(Y* obj, void (X::*func)(const T& p1)) {
        unregisterDelegate(Gallant::MakeDelegate(obj, func));
    }

protected:

    template <typename T>
    void raiseEvent(const T& event) const {
        details::SignalSelector<T, EventType, Others...> selector;
        auto manager = (details::SignalManager<T>*)this;
        selector.getEventHandler(manager)(event);
    }
};

NS_FT_END