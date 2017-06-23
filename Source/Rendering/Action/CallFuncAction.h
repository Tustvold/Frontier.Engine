#pragma once
#include "Action.h"

NS_FT_BEGIN

class CallFuncAction : public Action {
public:
    explicit CallFuncAction(void(*func)(Node*));
    virtual ~CallFuncAction();
    virtual void onStart(Node* node) override;
    
protected:
    void(*func_)(Node* node);
};

NS_FT_END