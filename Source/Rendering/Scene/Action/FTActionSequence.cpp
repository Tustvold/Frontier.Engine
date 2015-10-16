#include "FTActionSequence.h"

FTActionSequence::FTActionSequence() : action_index_(0) {
}

FTActionSequence::~FTActionSequence() {
}

void FTActionSequence::addAction(std::unique_ptr<FTAction>&& action) {
    FTAssert(action, "Trying to add null action");
    actions_.push_back(std::move(action));
}

void FTActionSequence::onStart(FTNode* node) {
    FTAction::onStart(node);
    FTAssert(actions_.size() != 0, "A sequence must contain at least one action");
    action_index_ = 0;
    actions_[action_index_]->onStart(node);
}

void FTActionSequence::onUpdate(FTNode* node, const FTUpdateEvent& event) {
    auto& current_action = actions_[action_index_];
    
    if (!current_action->getCompleted())
        current_action->onUpdate(node, event);

    if (current_action->getCompleted()) {
        action_index_++;
        if (action_index_ == actions_.size()) {
            setCompleted();
            return;
        }
       actions_[action_index_]->onStart(node);
    }
}