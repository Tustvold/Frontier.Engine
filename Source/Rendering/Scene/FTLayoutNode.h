#pragma once
#include "FTNode.h"

template <typename ShaderProgram>
class FTLayoutNode : public FTNode<ShaderProgram> {
public:
    FTLayoutNode() {
        
    }

    virtual ~FTLayoutNode() {
        
    }

    void addChild(const std::shared_ptr<FTNodeBase>& child) {
        children_.push_back(child);
    }

    void visitChildren(const std::shared_ptr<FTCamera>& camera, std::stack<glm::mat4>& matrix_stack) override {
        for (auto it = children_.begin(); it != children_.end(); ++it) {
            (*it)->visit(camera, matrix_stack);
        }
    }
    
protected:
    std::vector<std::shared_ptr<FTNodeBase>> children_;
};