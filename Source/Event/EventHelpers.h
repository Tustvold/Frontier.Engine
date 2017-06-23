#pragma once
#include <ThirdParty/Signals/Signal.h>

NS_FT_BEGIN

// Internal utility templates - do not use
namespace details
{
    template <typename EventType>
    class SignalManager {
    public:

        Gallant::Signal1<const EventType&>& getEventHandler() {
            return signal_;
        }


    protected:
        Gallant::Signal1<const EventType&> signal_;

        SignalManager() {

        }

        ~SignalManager() {

        }
    };


    template <typename ProvidedEventType, typename... Events>
    struct SignalSelector {
    };

    // When delegate found stop recurring
    template <typename ProvidedEventType, typename... Others>
    struct SignalSelector<ProvidedEventType, ProvidedEventType, Others...> {

        virtual ~SignalSelector() {

        }

        Gallant::Signal1<const ProvidedEventType&>& getEventHandler(SignalManager<ProvidedEventType>* manager) {
            return manager->getEventHandler();
        }
    };

    // Delegate not found - keep going
    template <typename ProvidedEventType, typename EventType, typename... Others>
    struct SignalSelector<ProvidedEventType, EventType, Others...> : SignalSelector<ProvidedEventType, Others...> {
        static_assert(sizeof...(Others) != 0, "Dispatcher does not support event");

        virtual ~SignalSelector() {

        }
    };
}

NS_FT_END