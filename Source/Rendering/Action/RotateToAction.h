#pragma once
#include "IntervalAction.h"

NS_FT_BEGIN

class RotateToAction : public IntervalAction {
public:
    explicit RotateToAction(const glm::quat& quat, double time);

    void onStart(Node* node) override;

    void onUpdate(Node* node, const UpdateEvent& event) override;
protected:
    glm::quat from_quat_;
    glm::quat to_quat_;
};

NS_FT_END