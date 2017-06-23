#pragma once
#include "FTAction.h"
#include <ThirdParty/Signals/Delegate.h>

NS_FT_BEGIN

class FTCallDelegateAction : public FTAction {
public:
    
    template <typename X, typename Y>
    FTCallDelegateAction(Y* obj, void (X::*func)(void)) : delegate_(Gallant::MakeDelegate(obj, func)) {
        
    }

    explicit FTCallDelegateAction(const Gallant::Delegate0<>& delegate) : delegate_(delegate) {
        
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

NS_FT_END