#include "FTCameraFPS.h"
#include <FTEngine.h>
#include <Frontier.h>
#include <Event/Mouse/FTMouseEvents.h>
#include <Event/Mouse/FTMouseEventDispatcher.h>
#include <Event/Engine/FTEngineEventDispatcher.h>
#include <Event/FTEventManager.h>

FTCameraFPS::FTCameraFPS() : move_speed_(15.0f), rotation_speed_(0.005f) {
    auto input_manager = FTEngine::getInputManager();
    forward_state_ = input_manager->getKeyState("Forward", GLFW_KEY_W);
    back_state_ = input_manager->getKeyState("Back", GLFW_KEY_S);
    left_state_ = input_manager->getKeyState("Left", GLFW_KEY_A);
    right_state_ = input_manager->getKeyState("Right", GLFW_KEY_D);
    up_state_ = input_manager->getKeyState("Up", GLFW_KEY_SPACE);
    down_state_ = input_manager->getKeyState("Down", GLFW_KEY_LEFT_SHIFT);
    freeze_frustrum_state_ = input_manager->getKeyState("Freeze Frustrum", GLFW_KEY_EQUAL);

    FTEngine::getEventManager()->registerDelegate<FTEngineEventDispatcher>(this, &FTCameraFPS::update);
    FTEngine::getEventManager()->registerDelegate<FTMouseEventDispatcher>(this, &FTCameraFPS::mouseMoveEvent);
}


FTCameraFPS::~FTCameraFPS() {
    FTEngine::getEventManager()->unregisterDelegate<FTEngineEventDispatcher>(this, &FTCameraFPS::update);
    FTEngine::getEventManager()->unregisterDelegate<FTMouseEventDispatcher>(this, &FTCameraFPS::mouseMoveEvent);
}

void FTCameraFPS::update(const FTUpdateEvent& event) {
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

void FTCameraFPS::mouseMoveEvent(const FTMouseMoveEvent& event) {
    rotation_euler_radians_.x += event.delta_.x * rotation_speed_;
    rotation_euler_radians_.y += event.delta_.y * rotation_speed_;

    if (rotation_euler_radians_.y > M_PI / 2.0f)
        rotation_euler_radians_.y = (float)M_PI / 2.0f;
    else if (rotation_euler_radians_.y < -M_PI / 2.0f)
        rotation_euler_radians_.y = -(float)M_PI / 2.0f;


    setRotation(glm::angleAxis(rotation_euler_radians_.y, right_vector_) * glm::angleAxis(-rotation_euler_radians_.x, up_axis_));
}
