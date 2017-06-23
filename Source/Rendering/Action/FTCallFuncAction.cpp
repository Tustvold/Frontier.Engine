#include "FTCallFuncAction.h"

NS_FT_BEGIN

FTCallFuncAction::FTCallFuncAction(void(*func)(FTNode*)) : func_(func) {

}

FTCallFuncAction::~FTCallFuncAction() {
}

void FTCallFuncAction::onStart(FTNode* node) {
    FTAction::onStart(node);
    func_(node);
    setCompleted();
}

NS_FT_END