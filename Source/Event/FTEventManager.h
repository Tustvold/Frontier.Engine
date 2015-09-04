#pragma once

#include <memory>
#include <unordered_map>
#include <typeindex>

class FTEventDispatcherBase;

class FTEventManager {
    friend class FTEngine;
public:


    static FTEventManager* getSharedInstance();

    void registerDispatcher(const std::shared_ptr<FTEventDispatcherBase>& dispatcher);

private:
    FTEventManager();
    ~FTEventManager();

    std::unordered_map<std::type_index, std::shared_ptr<FTEventDispatcherBase>> event_dispatchers_;
};