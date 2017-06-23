#include "CallFuncAction.h"

NS_FT_BEGIN

CallFuncAction::CallFuncAction(void(*func)(Node*)) : func_(func) {

}

CallFuncAction::~CallFuncAction() {
}

void CallFuncAction::onStart(Node* node) {
    Action::onStart(node);
    func_(node);
    setCompleted();
}

NS_FT_END