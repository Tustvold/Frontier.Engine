#include "FTCameraFPS.h"
#include <FTEngine.h>
#include <Frontier.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Event/Mouse/FTMouseEvents.h>
#include <Event/Mouse/FTMouseEventDispatcher.h>

FTCameraFPS::FTCameraFPS() : move_speed_(15.0f), rotation_speed_(0.005f) {
    auto input_manager = FTEngine::getInputManager();
    forward_state_ = input_manager->getKeyState("Forward", GLFW_KEY_W);
    back_state_ = input_manager->getKeyState("Back", GLFW_KEY_S);
    left_state_ = input_manager->getKeyState("Left", GLFW_KEY_A);
    right_state_ = input_manager->getKeyState("Right", GLFW_KEY_D);
    up_state_ = input_manager->getKeyState("Up", GLFW_KEY_SPACE);
    down_state_ = input_manager->getKeyState("Down", GLFW_KEY_LEFT_SHIFT);

    auto pre_draw_delegate = Gallant::Delegate1<const FTPreDrawEvent&>(this, &FTCameraFPS::update);
    FTEngine::getEventManager()->getEventDispatcher<FTEngineEventDispatcher>()->registerDelegate(pre_draw_delegate);

    auto mouse_move_delegate = Gallant::Delegate1<const FTMouseMoveEvent&>(this, &FTCameraFPS::mouseMoveEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTMouseEventDispatcher>()->registerDelegate(mouse_move_delegate);
}


FTCameraFPS::~FTCameraFPS() {
    auto pre_draw_delegate = Gallant::Delegate1<const FTPreDrawEvent&>(this, &FTCameraFPS::update);
    FTEngine::getEventManager()->getEventDispatcher<FTEngineEventDispatcher>()->unregisterDelegate(pre_draw_delegate);

    auto mouse_move_delegate = Gallant::Delegate1<const FTMouseMoveEvent&>(this, &FTCameraFPS::mouseMoveEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTMouseEventDispatcher>()->unregisterDelegate(mouse_move_delegate);
}

void FTCameraFPS::update(const FTPreDrawEvent& event) {
    float dt = (float)event.delta_time_;

    if (forward_state_->isPressed()) {
        position_ += look_direction_ * dt * move_speed_;
        view_matrix_dirty_ = true;
    }

    if (back_state_->isPressed()) {
        position_ -= look_direction_ * dt * move_speed_;
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
        position_.y += dt * move_speed_;
        view_matrix_dirty_ = true;
    }

    if (down_state_->isPressed()) {
        position_.y -= dt * move_speed_;
        view_matrix_dirty_ = true;
    }
}

void FTCameraFPS::mouseMoveEvent(const FTMouseMoveEvent& event) {
    rotation_euler_radians.x += event.delta_x_ * rotation_speed_;
    rotation_euler_radians.y -= event.delta_y_ * rotation_speed_;

    if (rotation_euler_radians.y > M_PI / 2.0f)
        rotation_euler_radians.y = (float)M_PI / 2.0f;
    else if (rotation_euler_radians.y < -M_PI / 2.0f)
        rotation_euler_radians.y = -(float)M_PI / 2.0f;


    rotation_dirty_ = true;
    view_matrix_dirty_ = true;
}