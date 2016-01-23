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
    FTEngine::getEventManager()->registerDelegate<FTKeyboardEventDispatcher>(this, &FTInputManager::keyRepeatEvent);
    FTEngine::getEventManager()->registerDelegate<FTKeyboardEventDispatcher>(this, &FTInputManager::keyReleasedEvent);
    FTEngine::getEventManager()->registerDelegate<FTMouseEventDispatcher>(this, &FTInputManager::mouseButtonPressedEvent);
    FTEngine::getEventManager()->registerDelegate<FTMouseEventDispatcher>(this, &FTInputManager::mouseButtonReleasedEvent);
    FTEngine::getEventManager()->registerDelegate<FTMouseEventDispatcher>(this, &FTInputManager::mouseMovedEvent);
    FTEngine::getEventManager()->registerDelegate<FTMouseEventDispatcher>(this, &FTInputManager::mouseExitEvent);
}

FTInputManager::~FTInputManager() {
    FTLOG("Input Manager destroyed");
    // As the input manager is destroyed after the EventManager we don't unregister the events registered in setup
}


const std::shared_ptr<FTKeyMapping>& FTInputManager::getKeyState(const std::string& name, int default_key, int default_mods) {
    auto it = name_to_key_state_.find(name);
    if (it == name_to_key_state_.end()) {
        auto map = std::make_shared<FTKeyMapping>();
        if (default_key != GLFW_KEY_UNKNOWN)
            map->addMapping(default_key, default_mods);
        addKeyboardDelegate(map.get());
        name_to_key_state_[name] = std::move(map);
        it = name_to_key_state_.find(name);
    }
    FTAssert(it != name_to_key_state_.end(), "Failed to add key state");
    return it->second;
}

void FTInputManager::keyPressedEvent(const FTKeyPressedEvent& event) {
    FTAssert(event.key_ >= 0 && event.key_ <= GLFW_KEY_LAST, "Invalid Key");

    FTKeyboardDelegate* delegate = nullptr;
    for (auto it = keyboard_delegates_.begin(); it != keyboard_delegates_.end(); ++it) {
        if ((*it)->getKeyboardDelegateEnabled() && (*it)->onKeyPressed(event)) {
            delegate = *it;
            break;
        }
    }
    if (delegate == nullptr)
        return;
    active_keyboard_delegates_[event.key_] = delegate;
}

void FTInputManager::keyRepeatEvent(const FTKeyRepeatEvent& event) {
    auto it = active_keyboard_delegates_.find(event.key_);
    if (it == active_keyboard_delegates_.end())
        return;
    it->second->onKeyRepeat(event);
}

void FTInputManager::keyReleasedEvent(const FTKeyReleasedEvent& event) {
    if (event.key_ == GLFW_KEY_UNKNOWN)
        return;
    FTAssert(event.key_ >= 0 && event.key_ <= GLFW_KEY_LAST, "Invalid Key");
    
    auto it = active_keyboard_delegates_.find(event.key_);
    if (it == active_keyboard_delegates_.end())
        return;
    it->second->onKeyRelease(event);
    active_keyboard_delegates_.erase(it);
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


void FTInputManager::sortMouseDelegates() {
    std::stable_sort(mouse_delegates_.begin(), mouse_delegates_.end(), [](FTMouseDelegate* a, FTMouseDelegate* b) {
                         return a->getMouseDelegatePriority() > b->getMouseDelegatePriority();
                     });
}

void FTInputManager::mouseDelegatePriorityChange(FTMouseDelegate* mouse_delegate) {
    sortMouseDelegates();
}

void FTInputManager::sortKeyboardDelegates() {
    std::stable_sort(keyboard_delegates_.begin(), keyboard_delegates_.end(), [](FTKeyboardDelegate* a, FTKeyboardDelegate* b) {
        return a->getKeyboardDelegatePriority() > b->getKeyboardDelegatePriority();
    });
}

void FTInputManager::keyboardDelegatePriorityChange(FTKeyboardDelegate* ft_keyboard_delegate) {
    sortKeyboardDelegates();
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

void FTInputManager::addKeyboardDelegate(FTKeyboardDelegate* delegate) {
    // TODO Insert into correct position instead of sorting whole array
    FTAssert(!delegate->is_added_, "Delegate already added");
    delegate->is_added_ = true;
    keyboard_delegates_.push_back(delegate);
    sortKeyboardDelegates();
}

void FTInputManager::removeKeyboardDelegate(FTKeyboardDelegate* delegate) {
    FTAssert(delegate->is_added_, "Delegate not added");

    for (auto it = active_keyboard_delegates_.begin(); it != active_keyboard_delegates_.end();) {
        if (it->second == delegate) {
            it = active_keyboard_delegates_.erase(it);
        } else {
            ++it;
        }
    }

    auto it = std::find(keyboard_delegates_.begin(), keyboard_delegates_.end(), delegate);
    FTAssert(it != keyboard_delegates_.end(), "Couldn't find mouse delegate to remove");
    (*it)->is_added_ = false;
    keyboard_delegates_.erase(it);
}
