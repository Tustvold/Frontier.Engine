#pragma once
#include "FTAction.h"

class FTCallFuncAction : public FTAction {
public:
    explicit FTCallFuncAction(void(*func)(FTNode*));
    virtual ~FTCallFuncAction();
    virtual void onStart(FTNode* node) override;
    
protected:
    void(*func_)(FTNode* node);
};