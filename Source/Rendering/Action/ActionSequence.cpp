#include "ActionSequence.h"

NS_FT_BEGIN

ActionSequence::ActionSequence() : action_index_(0) {
}

ActionSequence::~ActionSequence() {
}

void ActionSequence::addAction(std::unique_ptr<Action>&& action) {
    FTAssert(action, "Trying to add null action");
    actions_.push_back(std::move(action));
}

void ActionSequence::onStart(Node* node) {
    Action::onStart(node);
    FTAssert(actions_.size() != 0, "A sequence must contain at least one action");
    action_index_ = 0;
    actions_[action_index_]->onStart(node);
}

void ActionSequence::onUpdate(Node* node, const UpdateEvent& event) {

    while (true) {
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
            continue;
        }
        break;
    }
}

NS_FT_END