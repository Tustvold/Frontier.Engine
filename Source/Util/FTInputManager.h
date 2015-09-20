#pragma once
#include <GL/glew.h>
#include <ThirdParty/Signals/Signal.h>
#include <Rendering/FTDirector.h>
#include <Frontier.h>
#include <glfw3.h>
#include <unordered_map>
#include <Event/Engine/FTEngineEvents.h>


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
    // This is baked into pressed_count_ at the next draw event
    int released_count_;
};

// Singleton which handles input
// Will in future support rebinding keys
class FTInputManager {
    friend class FTEngine;
public:
    
    const std::shared_ptr<FTKeyState>& getKeyState(const std::string& name, int default_mapping = GLFW_KEY_UNKNOWN);
    void addMapping(const std::string& name, int key);

    
private:

    FTInputManager();
    ~FTInputManager();

    void setup();

    void keyPressedEvent(const FTKeyPressedEvent& event);
    void keyReleasedEvent(const FTKeyReleasedEvent& event);
    void update(const FTPreDrawEvent& event);

    std::unordered_map<std::string, std::shared_ptr<FTKeyState>> name_to_key_state_;
    std::vector<std::shared_ptr<FTKeyState>> key_to_state_[GLFW_KEY_LAST + 1];
};
