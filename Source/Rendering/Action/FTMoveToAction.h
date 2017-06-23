#pragma once
#include "FTIntervalAction.h"

NS_FT_BEGIN

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

NS_FT_END