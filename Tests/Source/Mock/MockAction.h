#pragma once
#include <Rendering/Action/Action.h>

NS_FT_BEGIN

class MockAction : public Action {

public:
    MOCK_METHOD1(onStart, void(Node* node));
    MOCK_METHOD2(onUpdate, void(Node* node, const UpdateEvent& event));
    MOCK_METHOD0(destroyed, void());


    virtual ~MockAction() {
        destroyed();
    }

    void callParentOnStart(Node* node) {
        Action::onStart(node);
    }
};

NS_FT_END