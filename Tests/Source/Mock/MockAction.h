#pragma once
#include <Rendering/Scene/Action/FTAction.h>

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