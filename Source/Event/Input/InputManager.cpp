#include "InputManager.h"
#include <Event/Keyboard/KeyboardEventDispatcher.h>
#include <Event/EventManager.h>
#include <Event/Engine/EngineEventDispatcher.h>
#include <algorithm>
#include <Engine.h>

NS_FT_BEGIN

InputManager::InputManager(): mouse_delegates_protected_(false), keyboard_delegates_protected_(false) {

}

void InputManager::setup() {
    Engine::getEventManager()->registerDelegate<KeyboardEventDispatcher>(this, &InputManager::keyPressedEvent);
    Engine::getEventManager()->registerDelegate<KeyboardEventDispatcher>(this, &InputManager::keyRepeatEvent);
    Engine::getEventManager()->registerDelegate<KeyboardEventDispatcher>(this, &InputManager::keyReleasedEvent);
    Engine::getEventManager()->registerDelegate<MouseEventDispatcher>(this, &InputManager::mouseButtonPressedEvent);
    Engine::getEventManager()->registerDelegate<MouseEventDispatcher>(this, &InputManager::mouseButtonReleasedEvent);
    Engine::getEventManager()->registerDelegate<MouseEventDispatcher>(this, &InputManager::mouseMovedEvent);
    Engine::getEventManager()->registerDelegate<MouseEventDispatcher>(this, &InputManager::mouseExitEvent);
}

InputManager::~InputManager() {
    FTLOG("Input Manager destroyed");
    // As the input manager is destroyed after the EventManager we don't unregister the events registered in setup
}


const std::shared_ptr<KeyMapping>& InputManager::getKeyState(const std::string& name, int default_key, int default_mods) {
    auto it = name_to_key_state_.find(name);
    if (it == name_to_key_state_.end()) {
        auto map = std::make_shared<KeyMapping>();
        if (default_key != GLFW_KEY_UNKNOWN)
            map->addMapping(default_key, default_mods);
        addKeyboardDelegate(map.get());
        name_to_key_state_[name] = std::move(map);
        it = name_to_key_state_.find(name);
    }
    FTAssert(it != name_to_key_state_.end(), "Failed to add key state");
    return it->second;
}

void InputManager::keyPressedEvent(const KeyPressedEvent& event) {
    FTAssert(event.key_ >= 0 && event.key_ <= GLFW_KEY_LAST, "Invalid Key");

    FTAssert(active_keyboard_delegates_.find(event.key_) == active_keyboard_delegates_.end(), "Delegates already added for event");


    std::vector<KeyboardDelegate*> delegates;
    keyboard_delegates_protected_ = true;
    for (auto it = keyboard_delegates_.begin(); it != keyboard_delegates_.end(); ++it) {
        if ((*it)->getKeyboardDelegateEnabled() && (*it)->onKeyPressed(event)) {
            delegates.push_back(*it);
            if ((*it)->getSwallowsEvents())
                break;
        }
    }
    keyboard_delegates_protected_ = false;

    if (delegates.size() == 0)
        return;
    active_keyboard_delegates_[event.key_] = std::move(delegates);
}

void InputManager::keyRepeatEvent(const KeyRepeatEvent& event) {
    auto it = active_keyboard_delegates_.find(event.key_);
    if (it == active_keyboard_delegates_.end())
        return;

    for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
        if ((*it2)->getKeyboardDelegateEnabled())
            (*it2)->onKeyRepeat(event);
    }
}

void InputManager::keyReleasedEvent(const KeyReleasedEvent& event) {
    if (event.key_ == GLFW_KEY_UNKNOWN)
        return;
    FTAssert(event.key_ >= 0 && event.key_ <= GLFW_KEY_LAST, "Invalid Key");

    auto it = active_keyboard_delegates_.find(event.key_);
    if (it == active_keyboard_delegates_.end())
        return;

    for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
        if ((*it2)->getKeyboardDelegateEnabled())
            (*it2)->onKeyRelease(event);
    }

    active_keyboard_delegates_.erase(it);
}

void InputManager::mouseButtonPressedEvent(const MouseButtonPressedEvent& event) {
    FTAssert(event.mouse_button_ >= 0 && event.mouse_button_ < GLFW_MOUSE_BUTTON_LAST + 1, "Invalid Mouse Button Pressed");
    FTAssert(active_mouse_delegates_[event.mouse_button_].size() == 0, "Mouse Button already pressed");

    std::vector<MouseDelegate*> delegates;

    mouse_delegates_protected_ = true;
    for (auto it = mouse_delegates_.begin(); it != mouse_delegates_.end(); ++it) {
        if ((*it)->getMouseDelegateEnabled() && (*it)->onMouseDown(event)) {
            delegates.push_back(*it);
            if ((*it)->getSwallowsEvents())
                break;
        }
    }
    mouse_delegates_protected_ = false;
    active_mouse_delegates_[event.mouse_button_] = std::move(delegates);
}

void InputManager::mouseButtonReleasedEvent(const MouseButtonReleasedEvent& event) {
    FTAssert(event.mouse_button_ >= 0 && event.mouse_button_ < GLFW_MOUSE_BUTTON_LAST + 1, "Invalid Mouse Button Pressed");
    auto& list = active_mouse_delegates_[event.mouse_button_];

    for (auto it = list.begin(); it != list.end(); ++it) {
        (*it)->onMouseRelease(event);
    }
    list.clear();
}

void InputManager::mouseMovedEvent(const MouseMoveEvent& event) {
    for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST + 1; i++) {
        auto& list = active_mouse_delegates_[i];
        for (auto it = list.begin(); it != list.end(); ++it) {
            if ((*it)->getMouseDelegateEnabled())
                (*it)->onMouseDrag(event, i);
        }
    }
}

void InputManager::mouseExitEvent(const MouseExitEvent& event) {
    for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST + 1; i++) {
        auto& list = active_mouse_delegates_[i];
        for (auto it = list.begin(); it != list.end(); ++it) {
            if ((*it)->getMouseDelegateEnabled())
                (*it)->onMouseRelease(MouseButtonReleasedEvent(glm::vec2(-1, -1), i, true));
        }
        list.clear();
    }
}

void InputManager::sortDelegates() {
    sortMouseDelegates();
    sortKeyboardDelegates();
}

void InputManager::sortMouseDelegates() {
    FTAssert(!mouse_delegates_protected_, "Mouse Delegates cannot be modified");
    mouse_delegates_protected_ = true;
    std::stable_sort(mouse_delegates_.begin(), mouse_delegates_.end(), [](MouseDelegate* a, MouseDelegate* b) {
                         return a->getMouseDelegatePriority() > b->getMouseDelegatePriority();
                     });
    mouse_delegates_protected_ = false;
}

void InputManager::sortKeyboardDelegates() {
    FTAssert(!keyboard_delegates_protected_, "Keyboard Delegates cannot be modified");
    keyboard_delegates_protected_ = true;
    std::stable_sort(keyboard_delegates_.begin(), keyboard_delegates_.end(), [](KeyboardDelegate* a, KeyboardDelegate* b) {
                         return a->getKeyboardDelegatePriority() > b->getKeyboardDelegatePriority();
                     });
    keyboard_delegates_protected_ = false;
}

void InputManager::addMouseDelegate(MouseDelegate* delegate) {
    FTAssert(!mouse_delegates_protected_, "Mouse Delegates cannot be modified");
    FTAssert(!delegate->is_added_, "Delegate already added");
    delegate->is_added_ = true;
    
    mouse_delegates_.push_back(delegate);
    sortMouseDelegates();
}

void InputManager::removeMouseDelegate(MouseDelegate* delegate) {
    FTAssert(delegate->is_added_, "Delegate not added");

    for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST + 1; i++) {
        auto& list = active_mouse_delegates_[i];
        auto pos = std::find(list.begin(), list.end(), delegate);
        if (pos != list.end()) {
            list.erase(pos);
        }
    }

    FTAssert(!mouse_delegates_protected_, "Mouse Delegates cannot be modified");
    auto it = std::find(mouse_delegates_.begin(), mouse_delegates_.end(), delegate);
    FTAssert(it != mouse_delegates_.end(), "Couldn't find mouse delegate to remove");
    (*it)->is_added_ = false;
    mouse_delegates_.erase(it);
}

void InputManager::addKeyboardDelegate(KeyboardDelegate* delegate) {
    FTAssert(!keyboard_delegates_protected_, "Keyboard Delegates cannot be modified");
    FTAssert(!delegate->is_added_, "Delegate already added");
    delegate->is_added_ = true;
    keyboard_delegates_.push_back(delegate);
    sortKeyboardDelegates();
}

void InputManager::removeKeyboardDelegate(KeyboardDelegate* delegate) {
    FTAssert(delegate->is_added_, "Delegate not added");

    for (auto it = active_keyboard_delegates_.begin(); it != active_keyboard_delegates_.end(); ++it) {
        auto pos = std::find(it->second.begin(), it->second.end(), delegate);
        if (pos != it->second.end()) {
            it->second.erase(pos);
        }
    }
    FTAssert(!keyboard_delegates_protected_, "Keyboard Delegates cannot be modified")
    auto it = std::find(keyboard_delegates_.begin(), keyboard_delegates_.end(), delegate);
    FTAssert(it != keyboard_delegates_.end(), "Couldn't find mouse delegate to remove");
    (*it)->is_added_ = false;
    keyboard_delegates_.erase(it);
}

NS_FT_END