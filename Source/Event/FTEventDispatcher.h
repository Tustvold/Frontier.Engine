#pragma once

#include "FTEvent.h"
#include "FTEventHelpers.h"

class FTEventDispatcherBase {
public:
    virtual ~FTEventDispatcherBase() {
    }
};

// Base template declaration
template <typename... EventType>
class FTEventDispatcher {
};

// Sentinel template specialization
template <>
class FTEventDispatcher<> : public FTEventDispatcherBase {
public:
    virtual ~FTEventDispatcher() {

    }
};

// Recursive template specialization
template <typename EventType, typename... Others>
class FTEventDispatcher<EventType, Others...> : public FTEventDispatcher<Others...>, public details::FTSignalManager<EventType> {
public:
    static_assert(std::is_base_of<FTEvent, EventType>::value, "Event is not derived from FTEvent");

    virtual ~FTEventDispatcher() {

    }

    template <typename T>
    void registerDelegate(const Gallant::Delegate1<const T&>& delegate) {
        details::FTSignalSelector<T, EventType, Others...> selector;
        auto manager = (details::FTSignalManager<T>*)this;
        auto& eventHandler = selector.getEventHandler(manager);
        eventHandler.Connect(delegate);
    }

    template <typename T, typename X, typename Y>
    void registerDelegate(Y* obj, void (X::*func)(const T& p1)) {
        registerDelegate(Gallant::MakeDelegate(obj, func));
    }

    template <typename T>
    void unregisterDelegate(const Gallant::Delegate1<const T&>& delegate) {
        details::FTSignalSelector<T, EventType, Others...> selector;
        auto manager = (details::FTSignalManager<T>*)this;
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
        details::FTSignalSelector<T, EventType, Others...> selector;
        auto manager = (details::FTSignalManager<T>*)this;
        selector.getEventHandler(manager)(event);
    }
};
