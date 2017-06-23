#pragma once
#include "IntervalAction.h"

NS_FT_BEGIN

class MoveToAction : public IntervalAction {
public:
    MoveToAction(const glm::vec3& to_position, double time_interval);
    virtual ~MoveToAction();

    virtual void onStart(Node* node) override;
    virtual void onUpdate(Node* node, const UpdateEvent& event) override;

protected:
    const glm::vec3 to_position_;
    glm::vec3 from_position_;
    glm::vec3 delta_position_;
};

NS_FT_END