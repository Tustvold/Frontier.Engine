#pragma once
#include "FTIntervalAction.h"

class FTMoveToAction : public FTIntervalAction {
public:
    FTMoveToAction(const glm::vec3& to_position, double time_interval);
    virtual ~FTMoveToAction();

    virtual void onStart(FTNode* node) override;
    virtual void onUpdate(FTNode* node, const FTUpdateEvent& event) override;    

protected:
    const glm::vec3 to_position_;
    glm::vec3 from_position_;
    glm::vec3 delta_position_;
};