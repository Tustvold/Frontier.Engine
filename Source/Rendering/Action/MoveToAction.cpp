#include "MoveToAction.h"
#include <Rendering/Node.h>

NS_FT_BEGIN

MoveToAction::MoveToAction(const glm::vec3& to_position, double time_interval) : IntervalAction(time_interval), to_position_(to_position) {

}

MoveToAction::~MoveToAction() {
}


void MoveToAction::onStart(Node* node) {
    IntervalAction::onStart(node);
    if (progress_ == 1.0)
        node->setPosition(to_position_);

    from_position_ = node->getPosition();
    delta_position_ = to_position_ - from_position_;
}

void MoveToAction::onUpdate(Node* node, const UpdateEvent& event) {
    IntervalAction::onUpdate(node, event);
    node->setPosition(from_position_ + (float)progress_ * delta_position_);
}

NS_FT_END