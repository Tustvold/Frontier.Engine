#pragma once
#include <Event/Input/InputManager.h>
#include "Camera3D.h"

NS_FT_BEGIN

struct MouseMoveEvent;

class CameraFPS : public Camera3D {
public:
    explicit CameraFPS();
    virtual ~CameraFPS();


private:

    float move_speed_;
    float rotation_speed_;
    glm::vec2 rotation_euler_radians_;

    std::shared_ptr<KeyMapping> forward_state_;
    std::shared_ptr<KeyMapping> back_state_;
    std::shared_ptr<KeyMapping> left_state_;
    std::shared_ptr<KeyMapping> right_state_;
    std::shared_ptr<KeyMapping> up_state_;
    std::shared_ptr<KeyMapping> down_state_;
    std::shared_ptr<KeyMapping> freeze_frustrum_state_;

    void update(const UpdateEvent& event);
    void mouseMoveEvent(const MouseMoveEvent& event);
};

NS_FT_END