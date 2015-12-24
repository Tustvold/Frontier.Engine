#include "FTCallFuncAction.h"


FTCallFuncAction::FTCallFuncAction(void(*func)(FTNode*)) : func_(func) {

}

FTCallFuncAction::~FTCallFuncAction() {
}

void FTCallFuncAction::onStart(FTNode* node) {
    FTAction::onStart(node);
    func_(node);
    setCompleted();
}
