#include "RotateToAction.h"
#include <Rendering/Node.h>

NS_FT_BEGIN

RotateToAction::RotateToAction(const glm::quat& quat, double time) : IntervalAction(time), to_quat_(quat) {
}

void RotateToAction::onStart(Node* node) {
    IntervalAction::onStart(node);
    from_quat_ = node->getRotationQuaternion();
    if (progress_ == 1.0)
        node->setRotationQuaternion(to_quat_);
}

void RotateToAction::onUpdate(Node* node, const UpdateEvent& event) {
    IntervalAction::onUpdate(node, event);
    node->setRotationQuaternion(glm::mix(from_quat_, to_quat_, (float)progress_));
}

NS_FT_END