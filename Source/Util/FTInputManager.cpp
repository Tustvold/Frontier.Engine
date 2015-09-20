#include "FTInputManager.h"
#include <Event/Keyboard/FTKeyboardEventDispatcher.h>
#include <Event/FTEventManager.h>
#include <Event/Engine/FTEngineEventDispatcher.h>

FTInputManager::FTInputManager() {
    
}

void FTInputManager::setup() {
    auto keyPressedDelegate = Gallant::Delegate1<const FTKeyPressedEvent&>(this, &FTInputManager::keyPressedEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTKeyboardEventDispatcher>()->registerDelegate(keyPressedDelegate);

    auto keyReleasedDelegate = Gallant::Delegate1<const FTKeyReleasedEvent&>(this, &FTInputManager::keyReleasedEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTKeyboardEventDispatcher>()->registerDelegate(keyReleasedDelegate);

    auto preDrawDelegate = Gallant::Delegate1<const FTPreDrawEvent&>(this, &FTInputManager::update);
    FTEngine::getEventManager()->getEventDispatcher<FTEngineEventDispatcher>()->registerDelegate(preDrawDelegate);
}

FTInputManager::~FTInputManager() {
    FTLOG("Input Manager destroyed");
    // As the input manager is destroyed after the EventManager we don't unregister the events registered in setup
}




const std::shared_ptr<FTKeyState>& FTInputManager::getKeyState(const std::string& name, int default_mapping) {
    auto it = name_to_key_state_.find(name);
    if (it == name_to_key_state_.end()) {
        name_to_key_state_[name] = std::make_shared<FTKeyState>();
        it = name_to_key_state_.find(name);
        if (default_mapping != GLFW_KEY_UNKNOWN) {
            FTAssert(default_mapping > 0 && default_mapping <= GLFW_KEY_LAST, "Invalid Mapping");
            key_to_state_[default_mapping].push_back(it->second);
        }
    }
    FTAssert(it != name_to_key_state_.end(), "Failed to add key state");
    return it->second;
}

void FTInputManager::addMapping(const std::string& name, int key) {
    auto& key_state = getKeyState(name);
    FTAssert(key > 0 && key <= GLFW_KEY_LAST, "Invalid Mapping");
    key_to_state_[key].push_back(key_state);
}

void FTInputManager::keyPressedEvent(const FTKeyPressedEvent& event) {
    FTAssert(event.key_ >= 0 && event.key_ <= GLFW_KEY_LAST, "Invalid Key");
    auto& key_states = key_to_state_[event.key_];
    for (auto it = key_states.begin(); it != key_states.end(); ++it) {
        (*it)->pressed_count_++;
    }
}

void FTInputManager::keyReleasedEvent(const FTKeyReleasedEvent& event) {
    FTAssert(event.key_ >= 0 && event.key_ <= GLFW_KEY_LAST, "Invalid Key");
    auto& key_states = key_to_state_[event.key_];
    for (auto it = key_states.begin(); it != key_states.end(); ++it) {
        (*it)->released_count_++;
    }
}

void FTInputManager::update(const FTPreDrawEvent& event) {
    for (auto it = name_to_key_state_.begin(); it != name_to_key_state_.end(); ++it) {
        auto& state = it->second;
        state->pressed_count_ -= state->released_count_;
        state->released_count_ = 0;
    }
}