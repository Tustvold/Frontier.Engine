#pragma once

#include <Frontier.h>
#include <unordered_map>
#include <typeindex>

class FTEventDispatcherBase;

class FTEventManager {
    friend class FTEngine;
public:

    template <typename Type>
    std::shared_ptr<Type> getEventDispatcher() {
        static_assert(std::is_base_of<FTEventDispatcherBase, Type>::value, "Dispatcher is not a subclass of FTEventDispatcherBase");
        auto it = event_dispatchers_.find(typeid(Type));
        if (it == event_dispatchers_.end()) {
            registerDispatcher<Type>(std::make_shared<Type>());
            it = event_dispatchers_.find(typeid(Type));
        }

        FTAssert(it != event_dispatchers_.end(), "EventDispatcher %s not found", typeid(Type).name());
        return std::static_pointer_cast<Type>(it->second);
    }

    template <typename Type>
    void registerDispatcher(const std::shared_ptr<Type>& dispatcher) {
        static_assert(std::is_base_of<FTEventDispatcherBase, Type>::value, "Dispatcher is not a subclass of FTEventDispatcherBase");
        const std::type_index& type = typeid(Type);
        FTAssert(event_dispatchers_.find(type) == event_dispatchers_.end(), "FTEventDispatcher already registered");
        event_dispatchers_[type] = dispatcher;
    }

    template <typename Dispatcher, typename Event, typename X, typename Y>
    void registerDelegate(Y* obj, void (X::*func)(const Event& p1)) {
        static_assert(std::is_base_of<FTEventDispatcherBase, Dispatcher>::value, "Dispatcher is not a subclass of FTEventDispatcherBase");
        std::shared_ptr<Dispatcher> dispatcher = getEventDispatcher<Dispatcher>();
        dispatcher->template registerDelegate<Event, X, Y>(obj, func);
    }

    template <typename Dispatcher, typename Event, typename X, typename Y>
    void unregisterDelegate(Y* obj, void (X::*func)(const Event& p1)) {
        static_assert(std::is_base_of<FTEventDispatcherBase, Dispatcher>::value, "Dispatcher is not a subclass of FTEventDispatcherBase");
        std::shared_ptr<Dispatcher> dispatcher = getEventDispatcher<Dispatcher>();
        dispatcher->template unregisterDelegate<Event, X, Y>(obj, func);
    }

private:
    FTEventManager();
    ~FTEventManager();

    std::unordered_map<std::type_index, std::shared_ptr<FTEventDispatcherBase>> event_dispatchers_;
};
