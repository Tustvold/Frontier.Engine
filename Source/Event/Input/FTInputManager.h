#pragma once
#include <vector>
#include <unordered_map>
#include <Frontier.h>
#include <Event/Engine/FTEngineEvents.h>
#include <Event/Input/FTMouseDelegate.h>


struct FTKeyReleasedEvent;
struct FTKeyPressedEvent;

struct FTKeyState {
    friend class FTInputManager;
public:
    FTKeyState() : pressed_count_(0), released_count_(0) {

    }

    bool isPressed() const {
        return pressed_count_ != 0;
    }

private:
    int pressed_count_;
    // This is baked into pressed_count_ at the next update event
    int released_count_;
};

// Singleton which handles input
class FTInputManager {
    friend class FTEngine;
    friend class FTMouseDelegate;
public:

    const std::shared_ptr<FTKeyState>& getKeyState(const std::string& name, int default_mapping = GLFW_KEY_UNKNOWN);
    void addMapping(const std::string& name, int key);

    void addMouseDelegate(FTMouseDelegate* delegate);

    void removeMouseDelegate(FTMouseDelegate* delegate);
private:

    FTInputManager();
    ~FTInputManager();

    void setup();

    void keyPressedEvent(const FTKeyPressedEvent& event);
    void keyReleasedEvent(const FTKeyReleasedEvent& event);

    void mouseButtonPressedEvent(const FTMouseButtonPressedEvent& event);
    void mouseButtonReleasedEvent(const FTMouseButtonReleasedEvent& event);
    void mouseMovedEvent(const FTMouseMoveEvent& event);
    void mouseExitEvent(const FTMouseExitEvent& event);

    void update(const FTUpdateEvent& event);
    void sortMouseDelegates();
    void mouseDelegatePriorityChange(FTMouseDelegate* mouse_delegate);

    std::unordered_map<std::string, std::shared_ptr<FTKeyState>> name_to_key_state_;
    std::vector<std::shared_ptr<FTKeyState>> key_to_state_[GLFW_KEY_LAST + 1];
    std::vector<FTMouseDelegate*> mouse_delegates_;
    FTMouseDelegate* active_mouse_delegates_[GLFW_MOUSE_BUTTON_LAST + 1];
};
