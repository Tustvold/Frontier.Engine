#include "FTInputManager.h"
#include <Event/Keyboard/FTKeyboardEventDispatcher.h>
#include <Event/FTEventManager.h>
#include <Event/Engine/FTEngineEventDispatcher.h>
#include <algorithm>
#include <FTEngine.h>

FTInputManager::FTInputManager() {
    for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST + 1; i++)
        active_mouse_delegates_[i] = nullptr;
}

void FTInputManager::setup() {
    FTEngine::getEventManager()->registerDelegate<FTKeyboardEventDispatcher>(this, &FTInputManager::keyPressedEvent);
    FTEngine::getEventManager()->registerDelegate<FTKeyboardEventDispatcher>(this, &FTInputManager::keyReleasedEvent);
    FTEngine::getEventManager()->registerDelegate<FTEngineEventDispatcher>(this, &FTInputManager::update);
    FTEngine::getEventManager()->registerDelegate<FTMouseEventDispatcher>(this, &FTInputManager::mouseButtonPressedEvent);
    FTEngine::getEventManager()->registerDelegate<FTMouseEventDispatcher>(this, &FTInputManager::mouseButtonReleasedEvent);
    FTEngine::getEventManager()->registerDelegate<FTMouseEventDispatcher>(this, &FTInputManager::mouseMovedEvent);
    FTEngine::getEventManager()->registerDelegate<FTMouseEventDispatcher>(this, &FTInputManager::mouseExitEvent);
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
    if (event.key_ == GLFW_KEY_UNKNOWN)
        return;
    FTAssert(event.key_ >= 0 && event.key_ <= GLFW_KEY_LAST, "Invalid Key");
    auto& key_states = key_to_state_[event.key_];
    for (auto it = key_states.begin(); it != key_states.end(); ++it) {
        (*it)->pressed_count_++;
    }
}

void FTInputManager::keyReleasedEvent(const FTKeyReleasedEvent& event) {
    if (event.key_ == GLFW_KEY_UNKNOWN)
        return;
    FTAssert(event.key_ >= 0 && event.key_ <= GLFW_KEY_LAST, "Invalid Key");
    auto& key_states = key_to_state_[event.key_];
    for (auto it = key_states.begin(); it != key_states.end(); ++it) {
        (*it)->released_count_++;
    }
}

void FTInputManager::mouseButtonPressedEvent(const FTMouseButtonPressedEvent& event) {
    FTAssert(event.mouse_button_ >= 0 && event.mouse_button_ < GLFW_MOUSE_BUTTON_LAST + 1, "Invalid Mouse Button Pressed");
    FTAssert(active_mouse_delegates_[event.mouse_button_] == nullptr, "Mouse Button already pressed");

    FTMouseDelegate* delegate = nullptr;
    for (auto it = mouse_delegates_.begin(); it != mouse_delegates_.end(); ++it) {
        if ((*it)->getMouseDelegateEnabled() && (*it)->onMouseDown(event)) {
            delegate = *it;
            break;
        }
    }
    active_mouse_delegates_[event.mouse_button_] = delegate;
}

void FTInputManager::mouseButtonReleasedEvent(const FTMouseButtonReleasedEvent& event) {
    FTAssert(event.mouse_button_ >= 0 && event.mouse_button_ < GLFW_MOUSE_BUTTON_LAST + 1, "Invalid Mouse Button Pressed");
    if (active_mouse_delegates_[event.mouse_button_] == nullptr)
        return;
    active_mouse_delegates_[event.mouse_button_]->onMouseRelease(event);
    active_mouse_delegates_[event.mouse_button_] = nullptr;
}

void FTInputManager::mouseMovedEvent(const FTMouseMoveEvent& event) {
    for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST + 1; i++) {
        if (active_mouse_delegates_[i] != nullptr) {
            if (active_mouse_delegates_[i]->getMouseDelegateEnabled())
                active_mouse_delegates_[i]->onMouseDrag(event, i);
        }
    }
}

void FTInputManager::mouseExitEvent(const FTMouseExitEvent& event) {
    for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST + 1; i++) {
        if (active_mouse_delegates_[i] != nullptr) {
            if (active_mouse_delegates_[i]->getMouseDelegateEnabled())
                active_mouse_delegates_[i]->onMouseRelease(FTMouseButtonReleasedEvent(glm::vec2(-1, -1), i, true));
            active_mouse_delegates_[i] = nullptr;
        }
    }
}

void FTInputManager::update(const FTUpdateEvent& event) {
    for (auto it = name_to_key_state_.begin(); it != name_to_key_state_.end(); ++it) {
        auto& state = it->second;
        state->pressed_count_ -= state->released_count_;
        state->released_count_ = 0;
    }
}

void FTInputManager::sortMouseDelegates() {
    std::stable_sort(mouse_delegates_.begin(), mouse_delegates_.end(), [](FTMouseDelegate* a, FTMouseDelegate* b) {
                         return a->getMouseDelegatePriority() > b->getMouseDelegatePriority();
                     });
}

void FTInputManager::mouseDelegatePriorityChange(FTMouseDelegate* mouse_delegate) {
    sortMouseDelegates();
}

void FTInputManager::addMouseDelegate(FTMouseDelegate* delegate) {
    // TODO Insert into correct position instead of sorting whole array
    FTAssert(!delegate->is_added_, "Delegate already added");
    delegate->is_added_ = true;
    mouse_delegates_.push_back(delegate);
    sortMouseDelegates();
}

void FTInputManager::removeMouseDelegate(FTMouseDelegate* delegate) {
    FTAssert(delegate->is_added_, "Delegate not added");

    for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST + 1; i++)
        if (active_mouse_delegates_[i] == delegate)
            active_mouse_delegates_[i] = nullptr;

    auto it = std::find(mouse_delegates_.begin(), mouse_delegates_.end(), delegate);
    FTAssert(it != mouse_delegates_.end(), "Couldn't find mouse delegate to remove");
    (*it)->is_added_ = false;
    mouse_delegates_.erase(it);
}
