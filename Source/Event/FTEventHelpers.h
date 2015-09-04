#include <ThirdParty/Signals/Signal.h>

// Internal utility templates - do not use
namespace details {
    template <typename EventType>
    class FTSignalManager {
    public:

        Gallant::Signal1<const EventType&>& getEventHandler() {
            return signal_;
        }


    protected:
        Gallant::Signal1<const EventType&> signal_;

        FTSignalManager() {
            
        }

        ~FTSignalManager() {
            
        }
    };


    template <typename ProvidedEventType, typename... Events>
    struct FTSignalSelector {};

    // When delegate found stop recurring
    template <typename ProvidedEventType, typename... Others>
    struct FTSignalSelector<ProvidedEventType, ProvidedEventType, Others...> {

        virtual ~FTSignalSelector() {

        }

        Gallant::Signal1<const ProvidedEventType&>& getEventHandler(FTSignalManager<ProvidedEventType>* manager) {
            return manager->getEventHandler();
        }
    };

    // Delegate not found - keep going
    template <typename ProvidedEventType, typename EventType, typename... Others>
    struct FTSignalSelector<ProvidedEventType, EventType, Others...> : FTSignalSelector<ProvidedEventType, Others...>{
        static_assert(sizeof...(Others) != 0, "Dispatcher does not support event");
        virtual ~FTSignalSelector() {

        }
    };
}
