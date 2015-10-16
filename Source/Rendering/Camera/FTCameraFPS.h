#pragma once
#include <Event/Input/FTInputManager.h>
#include "FTCamera3D.h"

struct FTMouseMoveEvent;

class FTCameraFPS : public FTCamera3D {
public:
    explicit FTCameraFPS();
    virtual ~FTCameraFPS();


private:

    float move_speed_;
    float rotation_speed_;

    std::shared_ptr<FTKeyState> forward_state_;
    std::shared_ptr<FTKeyState> back_state_;
    std::shared_ptr<FTKeyState> left_state_;
    std::shared_ptr<FTKeyState> right_state_;
    std::shared_ptr<FTKeyState> up_state_;
    std::shared_ptr<FTKeyState> down_state_;
    std::shared_ptr<FTKeyState> freeze_frustrum_state_;

    void update(const FTUpdateEvent& event);
    void mouseMoveEvent(const FTMouseMoveEvent& event);
};
