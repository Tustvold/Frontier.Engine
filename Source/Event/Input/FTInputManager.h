#pragma once
#include <vector>
#include <unordered_map>
#include <Frontier.h>
#include <Event/Engine/FTEngineEvents.h>
#include <Event/Input/FTMouseDelegate.h>
#include "FTKeyboardDelegate.h"
#include "FTKeyMapping.h"

struct FTKeyReleasedEvent;
struct FTKeyPressedEvent;

// Singleton which handles input
class FTInputManager {
    friend class FTEngine;
    friend class FTMouseDelegate;
    friend class FTKeyboardDelegate;
public:

    const std::shared_ptr<FTKeyMapping>& getKeyState(const std::string& name, int default_key = GLFW_KEY_UNKNOWN, int default_mods = 0);

    void addMouseDelegate(FTMouseDelegate* delegate);

    void removeMouseDelegate(FTMouseDelegate* delegate);

    void addKeyboardDelegate(FTKeyboardDelegate* delegate);

    void removeKeyboardDelegate(FTKeyboardDelegate* delegate);

private:

    FTInputManager();
    ~FTInputManager();

    void setup();

    void keyPressedEvent(const FTKeyPressedEvent& event);
    void keyRepeatEvent(const FTKeyRepeatEvent& event);
    void keyReleasedEvent(const FTKeyReleasedEvent& event);

    void mouseButtonPressedEvent(const FTMouseButtonPressedEvent& event);
    void mouseButtonReleasedEvent(const FTMouseButtonReleasedEvent& event);
    void mouseMovedEvent(const FTMouseMoveEvent& event);
    void mouseExitEvent(const FTMouseExitEvent& event);

    void sortMouseDelegates();
    void mouseDelegatePriorityChange(FTMouseDelegate* mouse_delegate);

    void sortKeyboardDelegates();
    void keyboardDelegatePriorityChange(FTKeyboardDelegate* ft_keyboard_delegate);

    std::unordered_map<std::string, std::shared_ptr<FTKeyMapping>> name_to_key_state_;

    std::vector<FTMouseDelegate*> mouse_delegates_;
    FTMouseDelegate* active_mouse_delegates_[GLFW_MOUSE_BUTTON_LAST + 1];

    std::vector<FTKeyboardDelegate*> keyboard_delegates_;
    std::unordered_map<int, FTKeyboardDelegate*> active_keyboard_delegates_;
};
