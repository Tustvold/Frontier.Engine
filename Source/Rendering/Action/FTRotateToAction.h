#pragma once
#include "FTIntervalAction.h"

class FTRotateToAction : public FTIntervalAction {
public:
    explicit FTRotateToAction(const glm::quat& quat, double time);

    void onStart(FTNode* node) override;

    void onUpdate(FTNode* node, const FTUpdateEvent& event) override;
protected:
    glm::quat from_quat_;
    glm::quat to_quat_;
};
