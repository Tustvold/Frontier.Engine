#pragma once
#include "FTAction.h"

NS_FT_BEGIN

class FTCallFuncAction : public FTAction {
public:
    explicit FTCallFuncAction(void(*func)(FTNode*));
    virtual ~FTCallFuncAction();
    virtual void onStart(FTNode* node) override;
    
protected:
    void(*func_)(FTNode* node);
};

NS_FT_END