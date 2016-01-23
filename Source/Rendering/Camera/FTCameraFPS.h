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

    std::shared_ptr<FTKeyMapping> forward_state_;
    std::shared_ptr<FTKeyMapping> back_state_;
    std::shared_ptr<FTKeyMapping> left_state_;
    std::shared_ptr<FTKeyMapping> right_state_;
    std::shared_ptr<FTKeyMapping> up_state_;
    std::shared_ptr<FTKeyMapping> down_state_;
    std::shared_ptr<FTKeyMapping> freeze_frustrum_state_;

    void update(const FTUpdateEvent& event);
    void mouseMoveEvent(const FTMouseMoveEvent& event);
};
