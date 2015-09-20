#pragma once

#include "FTEvent.h"
#include "FTEventHelpers.h"

class FTEventDispatcherBase {
public:
    virtual ~FTEventDispatcherBase() {
    }
};

// Base template declaration
template <typename... EventType> class FTEventDispatcher {};

// Sentinel template specialization
template <> class FTEventDispatcher<> : public FTEventDispatcherBase {
public:
    virtual ~FTEventDispatcher() {
        
    }
};

// Recursive template specialization
template <typename EventType, typename... Others> class FTEventDispatcher<EventType,Others...> : public FTEventDispatcher<Others...>, public details::FTSignalManager<EventType> {
public:
    static_assert(std::is_base_of<FTEvent, EventType>::value, "Event is not derived from FTEvent");
    
    virtual ~FTEventDispatcher() {
        
    }

    template <typename T>
    void registerDelegate(const Gallant::Delegate1<const T&>& delegate) const {
        details::FTSignalSelector<T, EventType, Others...> selector;
        auto manager = (details::FTSignalManager<T>*)this;
        auto& eventHandler = selector.getEventHandler(manager);
        eventHandler.Connect(delegate);
    }

    template <typename T>
    void unregisterDelegate(const Gallant::Delegate1<const T&>& delegate) const {
        details::FTSignalSelector<T, EventType, Others...> selector;
        auto manager = (details::FTSignalManager<T>*)this;
        auto& eventHandler = selector.getEventHandler(manager);
        eventHandler.Disconnect(delegate);
    }

protected:
    
    template <typename T>
    void raiseEvent(const T& event) const {
        details::FTSignalSelector<T, EventType, Others...> selector;
        auto manager = (details::FTSignalManager<T>*)this;
        selector.getEventHandler(manager)(event);
    }
};
