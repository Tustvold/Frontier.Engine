#pragma once
#include <GL/glew.h>
#include <ThirdParty/Signals/Signal.h>
#include <Rendering/FTDirector.h>
#include <Frontier.h>
#include <glfw3.h>

enum KeyState {
    KeyStatePressed = GLFW_PRESS,
    KeyStateReleased = GLFW_RELEASE
};

enum KeyName {
    KeyNameForward,
    KeyNameBackward,
    KeyNameLeft,
    KeyNameRight,
    KeyNameUp,
    KeyNameDown,
    KeyNameFreezeFrustrum,
    KeyNameFreeMouse,
    KeyNameOther //Must be last
};

// Singleton which handles input
// Will in future support rebinding keys
class FTInputManager {
    friend class FTEngine;
public:
    void registerWithWindow(GLFWwindow* window);

    Gallant::Signal2<KeyName, KeyState>* getButtonEventHandler() {
        return &button_event_handler_;
    }

    Gallant::Signal2<KeyName, float>* getButtonHeldEventHandler() {
        return &button_held_event_handler_;
    }

    Gallant::Signal2<float, float>* getCursorMovedEventHandler() {
        return &cursor_pos_update_event_handler_;
    }

    void setCursorPosition(float x, float y) {
        glfwSetCursorPos(window_, (double)x, (double)y);
    }

    bool isKeyDown(KeyName key) {
        return key_down_[key];
    }

private:

    FTInputManager();

    ~FTInputManager() {
        FTLOG("Input Manager destroyed");
        // FTDirector won't exist at this point so don't try to disconnect from it
        // FTDirector::getSharedInstance()->getPreDrawEventHandler()->Disconnect(this, &FTInputManager::update);
    };

    static void keyCallbackStatic(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void cursorPosCallbackStatic(GLFWwindow* window, double x, double y);
    static void cursorEnterCallback(GLFWwindow* window, int entered);

    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void cursorPosCallback(GLFWwindow* window, double x, double y);

    void update(float dt) {
        for (int i = 0; i < KeyNameOther; i++) {
            if (key_down_[i])
                button_held_event_handler_((KeyName)i, dt);
        }
    }

    KeyName key_mappings_[GLFW_KEY_LAST + 1];
    bool key_down_[KeyNameOther];
    static bool trust_mouse_;
    GLFWwindow* window_;

    Gallant::Signal2<KeyName, KeyState> button_event_handler_;
    Gallant::Signal2<KeyName, float> button_held_event_handler_;
    Gallant::Signal2<float, float> cursor_pos_update_event_handler_;
};
