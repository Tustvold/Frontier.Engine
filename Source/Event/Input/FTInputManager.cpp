#include "FTInputManager.h"
#include <Event/Keyboard/FTKeyboardEventDispatcher.h>
#include <Event/FTEventManager.h>
#include <Event/Engine/FTEngineEventDispatcher.h>
#include <algorithm>
#include <FTEngine.h>

FTInputManager::FTInputManager() {

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

    FTAssert(active_keyboard_delegates_.find(event.key_) == active_keyboard_delegates_.end(), "Delegates already added for event");


    std::vector<FTKeyboardDelegate*> delegates;
    for (auto it = keyboard_delegates_.begin(); it != keyboard_delegates_.end(); ++it) {
        if ((*it)->getKeyboardDelegateEnabled() && (*it)->onKeyPressed(event)) {
            delegates.push_back(*it);
            if ((*it)->getSwallowsEvents())
                break;
        }
    }

    if (delegates.size() == 0)
        return;
    active_keyboard_delegates_[event.key_] = std::move(delegates);
}

void FTInputManager::keyRepeatEvent(const FTKeyRepeatEvent& event) {
    auto it = active_keyboard_delegates_.find(event.key_);
    if (it == active_keyboard_delegates_.end())
        return;

    for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
        if ((*it2)->getKeyboardDelegateEnabled())
            (*it2)->onKeyRepeat(event);
    }
}

void FTInputManager::keyReleasedEvent(const FTKeyReleasedEvent& event) {
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

void FTInputManager::mouseButtonPressedEvent(const FTMouseButtonPressedEvent& event) {
    FTAssert(event.mouse_button_ >= 0 && event.mouse_button_ < GLFW_MOUSE_BUTTON_LAST + 1, "Invalid Mouse Button Pressed");
    FTAssert(active_mouse_delegates_[event.mouse_button_].size() == 0, "Mouse Button already pressed");

    std::vector<FTMouseDelegate*> delegates;

    for (auto it = mouse_delegates_.begin(); it != mouse_delegates_.end(); ++it) {
        if ((*it)->getMouseDelegateEnabled() && (*it)->onMouseDown(event)) {
            delegates.push_back(*it);
            if ((*it)->getSwallowsEvents())
                break;
        }
    }
    active_mouse_delegates_[event.mouse_button_] = std::move(delegates);
}

void FTInputManager::mouseButtonReleasedEvent(const FTMouseButtonReleasedEvent& event) {
    FTAssert(event.mouse_button_ >= 0 && event.mouse_button_ < GLFW_MOUSE_BUTTON_LAST + 1, "Invalid Mouse Button Pressed");
    auto& list = active_mouse_delegates_[event.mouse_button_];

    for (auto it = list.begin(); it != list.end(); ++it) {
        (*it)->onMouseRelease(event);
    }
    list.clear();
}

void FTInputManager::mouseMovedEvent(const FTMouseMoveEvent& event) {
    for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST + 1; i++) {
        auto& list = active_mouse_delegates_[i];
        for (auto it = list.begin(); it != list.end(); ++it) {
            if ((*it)->getMouseDelegateEnabled())
                (*it)->onMouseDrag(event, i);
        }
    }
}

void FTInputManager::mouseExitEvent(const FTMouseExitEvent& event) {
    for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST + 1; i++) {
        auto& list = active_mouse_delegates_[i];
        for (auto it = list.begin(); it != list.end(); ++it) {
            if ((*it)->getMouseDelegateEnabled())
                (*it)->onMouseRelease(FTMouseButtonReleasedEvent(glm::vec2(-1, -1), i, true));
        }
        list.clear();
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

    for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST + 1; i++) {
        auto& list = active_mouse_delegates_[i];
        auto pos = std::find(list.begin(), list.end(), delegate);
        if (pos != list.end()) {
            list.erase(pos);
        }
    }

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

    for (auto it = active_keyboard_delegates_.begin(); it != active_keyboard_delegates_.end(); ++it) {
        auto pos = std::find(it->second.begin(), it->second.end(), delegate);
        if (pos != it->second.end()) {
            it->second.erase(pos);
        }
    }

    auto it = std::find(keyboard_delegates_.begin(), keyboard_delegates_.end(), delegate);
    FTAssert(it != keyboard_delegates_.end(), "Couldn't find mouse delegate to remove");
    (*it)->is_added_ = false;
    keyboard_delegates_.erase(it);
}
