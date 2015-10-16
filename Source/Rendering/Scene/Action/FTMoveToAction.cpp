#include "FTMoveToAction.h"
#include <Rendering/Scene/FTNode.h>

FTMoveToAction::FTMoveToAction(const glm::vec3& to_position, double time_interval) : FTIntervalAction(time_interval), to_position_(to_position) {

}

FTMoveToAction::~FTMoveToAction() {
}


void FTMoveToAction::onStart(FTNode* node) {
    FTIntervalAction::onStart(node);
    from_position_ = node->getPosition();
    delta_position_ = to_position_ - from_position_;
}

void FTMoveToAction::onUpdate(FTNode* node, const FTUpdateEvent& event) {
    FTIntervalAction::onUpdate(node, event);
    node->setPosition(from_position_ + (float)progress_ * delta_position_);
}


