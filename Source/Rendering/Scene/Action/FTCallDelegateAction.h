#pragma once
#include "FTAction.h"
#include <ThirdParty/Signals/Delegate.h>

class FTCallDelegateAction : public FTAction {
public:
    
    template <typename X, typename Y>
    FTCallDelegateAction(Y* obj, void (X::*func)(void)) : delegate_(Gallant::MakeDelegate(obj, func)) {
        
    }

    virtual ~FTCallDelegateAction() {
        
    }

    virtual void onStart(FTNode* node) override {
        delegate_();
        setCompleted();
    }

protected:
    Gallant::Delegate0<> delegate_;
};