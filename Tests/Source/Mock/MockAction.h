#pragma once
#include <Rendering/Action/FTAction.h>

NS_FT_BEGIN

class MockAction : public FTAction {

public:
    MOCK_METHOD1(onStart, void(FTNode* node));
    MOCK_METHOD2(onUpdate, void(FTNode* node, const FTUpdateEvent& event));
    MOCK_METHOD0(destroyed, void());


    virtual ~MockAction() {
        destroyed();
    }

    void callParentOnStart(FTNode* node) {
        FTAction::onStart(node);
    }
};

NS_FT_END