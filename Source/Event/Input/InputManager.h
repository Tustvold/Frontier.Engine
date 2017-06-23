#pragma once
#include <vector>
#include <unordered_map>
#include <Frontier.h>
#include <Event/Engine/FTEngineEvents.h>
#include <Event/Input/MouseDelegate.h>
#include "KeyboardDelegate.h"
#include "KeyMapping.h"

NS_FT_BEGIN

struct KeyReleasedEvent;
struct KeyPressedEvent;

// Singleton which handles input
class InputManager {
    friend class Engine;
public:

    const std::shared_ptr<KeyMapping>& getKeyState(const std::string& name, int default_key = GLFW_KEY_UNKNOWN, int default_mods = 0);

    void addMouseDelegate(MouseDelegate* delegate);

    void removeMouseDelegate(MouseDelegate* delegate);

    void addKeyboardDelegate(KeyboardDelegate* delegate);

    void removeKeyboardDelegate(KeyboardDelegate* delegate);

    // Sort list of delegates based on their priority
    // Automatically called before glfwPollEvents
    void sortDelegates();
    void sortMouseDelegates();
    void sortKeyboardDelegates();

private:

    InputManager();
    ~InputManager();

    void setup();

    void keyPressedEvent(const KeyPressedEvent& event);
    void keyRepeatEvent(const KeyRepeatEvent& event);
    void keyReleasedEvent(const KeyReleasedEvent& event);

    void mouseButtonPressedEvent(const MouseButtonPressedEvent& event);
    void mouseButtonReleasedEvent(const MouseButtonReleasedEvent& event);
    void mouseMovedEvent(const MouseMoveEvent& event);
    void mouseExitEvent(const MouseExitEvent& event);
    
    

    std::unordered_map<std::string, std::shared_ptr<KeyMapping>> name_to_key_state_;

    std::vector<MouseDelegate*> mouse_delegates_;
    std::vector<MouseDelegate*> active_mouse_delegates_[GLFW_MOUSE_BUTTON_LAST + 1];

    std::vector<KeyboardDelegate*> keyboard_delegates_;
    std::unordered_map<int, std::vector<KeyboardDelegate*>> active_keyboard_delegates_;
    bool mouse_delegates_protected_;
    bool keyboard_delegates_protected_;
};

NS_FT_END