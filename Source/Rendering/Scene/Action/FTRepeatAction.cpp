#include "FTRepeatAction.h"

FTRepeatAction::FTRepeatAction(std::unique_ptr<FTAction>&& action, int repeat_count) : repeat_count_(repeat_count), remaining_count_(repeat_count_), action_(std::move(action)) {
    FTAssert(repeat_count > 0 || repeat_count == -1, "Repeat Count must be either positive or -1");
}

FTRepeatAction::~FTRepeatAction() {
}

void FTRepeatAction::onStart(FTNode* node) {
    FTAction::onStart(node);
    // The remaining_count_ is needed in order to properly reset this node
    remaining_count_ = repeat_count_;
    if (remaining_count_ != -1)
        remaining_count_--;

    action_->onStart(node);
}

void FTRepeatAction::onUpdate(FTNode* node, const FTUpdateEvent& event) {
    // If the action sets completed in onStart the next invocation will be in the next tick
    if (!action_->getCompleted())
        action_->onUpdate(node, event);
    if (action_->getCompleted()) {
        if (remaining_count_ == 0) {
            setCompleted();
            return;
        }
        if (remaining_count_ != -1)
            remaining_count_--;

        action_->onStart(node);
    }
}