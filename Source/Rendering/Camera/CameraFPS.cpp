#include "CameraFPS.h"
#include <Engine.h>
#include <Frontier.h>
#include <Event/Mouse/MouseEvents.h>
#include <Event/Mouse/MouseEventDispatcher.h>
#include <Event/Engine/EngineEventDispatcher.h>
#include <Event/EventManager.h>

NS_FT_BEGIN

CameraFPS::CameraFPS() : move_speed_(15.0f), rotation_speed_(0.005f) {
    auto input_manager = Engine::getInputManager();
    forward_state_ = input_manager->getKeyState("Forward", GLFW_KEY_W);
    back_state_ = input_manager->getKeyState("Back", GLFW_KEY_S);
    left_state_ = input_manager->getKeyState("Left", GLFW_KEY_A);
    right_state_ = input_manager->getKeyState("Right", GLFW_KEY_D);
    up_state_ = input_manager->getKeyState("Up", GLFW_KEY_SPACE);
    down_state_ = input_manager->getKeyState("Down", GLFW_KEY_LEFT_SHIFT);
    freeze_frustrum_state_ = input_manager->getKeyState("Freeze Frustrum", GLFW_KEY_EQUAL);

    Engine::getEventManager()->registerDelegate<EngineEventDispatcher>(this, &CameraFPS::update);
    Engine::getEventManager()->registerDelegate<MouseEventDispatcher>(this, &CameraFPS::mouseMoveEvent);
}


CameraFPS::~CameraFPS() {
    Engine::getEventManager()->unregisterDelegate<EngineEventDispatcher>(this, &CameraFPS::update);
    Engine::getEventManager()->unregisterDelegate<MouseEventDispatcher>(this, &CameraFPS::mouseMoveEvent);
}

void CameraFPS::update(const UpdateEvent& event) {
    float dt = (float)event.delta_time_;

    if (forward_state_->isPressed()) {
        position_ += look_vector_ * dt * move_speed_;
        view_matrix_dirty_ = true;
    }

    if (back_state_->isPressed()) {
        position_ -= look_vector_ * dt * move_speed_;
        view_matrix_dirty_ = true;
    }

    if (left_state_->isPressed()) {
        position_ -= right_vector_ * dt * move_speed_;
        view_matrix_dirty_ = true;
    }

    if (right_state_->isPressed()) {
        position_ += right_vector_ * dt * move_speed_;
        view_matrix_dirty_ = true;
    }

    if (up_state_->isPressed()) {
        position_ += up_axis_ * dt * move_speed_;
        view_matrix_dirty_ = true;
    }

    if (down_state_->isPressed()) {
        position_ -= up_axis_ * dt * move_speed_;
        view_matrix_dirty_ = true;
    }

    update_view_frustrum_ = !freeze_frustrum_state_->isPressed();
}

void CameraFPS::mouseMoveEvent(const MouseMoveEvent& event) {
    rotation_euler_radians_.x += event.delta_.x * rotation_speed_;
    rotation_euler_radians_.y += event.delta_.y * rotation_speed_;

    if (rotation_euler_radians_.y > M_PI / 2.0f)
        rotation_euler_radians_.y = (float)M_PI / 2.0f;
    else if (rotation_euler_radians_.y < -M_PI / 2.0f)
        rotation_euler_radians_.y = -(float)M_PI / 2.0f;

    setRotation(glm::angleAxis(-rotation_euler_radians_.x, up_axis_) * glm::angleAxis(rotation_euler_radians_.y, right_axis_));
}

NS_FT_END