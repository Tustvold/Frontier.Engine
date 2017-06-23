#pragma once
#include "Action.h"
#include <ThirdParty/Signals/Delegate.h>

NS_FT_BEGIN

class CallDelegateAction : public Action {
public:
    
    template <typename X, typename Y>
    CallDelegateAction(Y* obj, void (X::*func)(void)) : delegate_(Gallant::MakeDelegate(obj, func)) {
        
    }

    explicit CallDelegateAction(const Gallant::Delegate0<>& delegate) : delegate_(delegate) {
        
    }

    virtual ~CallDelegateAction() {
        
    }

    virtual void onStart(Node* node) override {
        delegate_();
        setCompleted();
    }

protected:
    Gallant::Delegate0<> delegate_;
};

NS_FT_END