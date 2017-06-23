#include "FTRotateToAction.h"
#include <Rendering/FTNode.h>

NS_FT_BEGIN

FTRotateToAction::FTRotateToAction(const glm::quat& quat, double time) : FTIntervalAction(time), to_quat_(quat) {
}

void FTRotateToAction::onStart(FTNode* node) {
    FTIntervalAction::onStart(node);
    from_quat_ = node->getRotationQuaternion();
    if (progress_ == 1.0)
        node->setRotationQuaternion(to_quat_);
}

void FTRotateToAction::onUpdate(FTNode* node, const FTUpdateEvent& event) {
    FTIntervalAction::onUpdate(node, event);
    node->setRotationQuaternion(glm::mix(from_quat_, to_quat_, (float)progress_));
}

NS_FT_END