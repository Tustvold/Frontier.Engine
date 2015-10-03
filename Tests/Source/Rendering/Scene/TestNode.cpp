#include <glfwmock.h>
#include <FTEngine.h>
#include <Rendering/Scene/FTNode.h>
#include <Mock/MockShader.h>
#include <Mock/ExpectUtils.h>
#include <Rendering/Camera/FTCamera2D.h>

class MockNodeDraw : public FTNode<MockShader> {

public:
    
    MOCK_METHOD0(pre_draw, void());
    MOCK_METHOD0(draw, void());
    MOCK_METHOD0(post_draw, void());
    MOCK_METHOD3(visitChildren, void(const std::shared_ptr<FTCamera>& camera, std::stack<glm::mat4>& matrix_stack, bool parent_updated));
};

class MockNodeChildren : public FTNode<MockShader> {
    std::vector<std::shared_ptr<FTNodeBase>> children_;
public:
    void visitChildren(const std::shared_ptr<FTCamera>& camera, std::stack<glm::mat4>& matrix_stack, bool parent_updated) override {
        for (auto it = children_.begin(); it != children_.end(); ++it) {
            (*it)->visit(camera, matrix_stack, parent_updated);
        }
    }

    MOCK_METHOD0(draw, void());

    void addChild(const std::shared_ptr<FTNodeBase>& child) {
        children_.push_back(child);
    }
};


TEST(TestNode, TestCallOrder) {
    GlfwMock mock;
    FTEngine::setup(true);

    auto camera = std::static_pointer_cast<FTCamera>(std::make_shared<FTCamera2D>());
    camera->setScreenRect(FTRect<int>(0, 0, 100, 100));
    std::stack<glm::mat4> matrix_stack;
    matrix_stack.push(glm::mat4());
    MockNodeDraw node;

    testing::InSequence s;
    EXPECT_CALL(node, pre_draw());
    EXPECT_CALL(node, draw());
    EXPECT_CALL(node, post_draw());
    EXPECT_CALL(node, visitChildren(camera, testing::_, testing::_));

    node.visit(camera, matrix_stack, false);

    FTEngine::cleanup();
}


TEST(TestNode, TestCulling) {
    GlfwMock mock;
    FTEngine::setup(true);

    auto camera = std::static_pointer_cast<FTCamera>(std::make_shared<FTCamera2D>());
    camera->setScreenRect(FTRect<int>(0, 0, 100, 100));
    std::stack<glm::mat4> matrix_stack;
    matrix_stack.push(glm::mat4());
    MockNodeChildren node;
    node.setSize(glm::vec2(50, 80));
    node.setFrustrumCull(true);
    
    EXPECT_CALL(node, draw());

    node.visit(camera, matrix_stack, false);


    testing::Mock::VerifyAndClearExpectations(&node);

    EXPECT_CALL(node, draw()).Times(0);

    node.setPosition(glm::vec2(-55, -85));

    node.visit(camera, matrix_stack, false);

    
    testing::Mock::VerifyAndClearExpectations(&node);

    EXPECT_CALL(node, draw()).Times(0);

    node.setPosition(glm::vec2(-0.1f, -0.1f));
    node.setAnchorPoint(glm::vec2(1.0f, 0.0f));
    
    node.visit(camera, matrix_stack, false);

    testing::Mock::VerifyAndClearExpectations(&node);

    EXPECT_CALL(node, draw()).Times(0);

    node.setPosition(glm::vec2(100.1f, 0.0f));
    node.setAnchorPoint(glm::vec2(0.0f, 0.0f));

    node.visit(camera, matrix_stack, false);

    testing::Mock::VerifyAndClearExpectations(&node);


    EXPECT_CALL(node, draw());

    node.setRotationQuaternion(glm::angleAxis((float)M_PI, glm::vec3(0, 0, 1)));

    node.visit(camera, matrix_stack, false);

    FTEngine::cleanup();
}

TEST(TestNode, TestCullingHierarchy) {
    GlfwMock mock;
    FTEngine::setup(true);

    auto camera = std::static_pointer_cast<FTCamera>(std::make_shared<FTCamera2D>());
    camera->setScreenRect(FTRect<int>(0, 0, 100, 100));
    std::stack<glm::mat4> matrix_stack;
    matrix_stack.push(glm::mat4());
    MockNodeChildren parent;
    auto child = std::make_shared<MockNodeChildren>();
    parent.addChild(std::static_pointer_cast<FTNodeBase>(child));
    child->setSize(glm::vec2(50, 80));
    child->setFrustrumCull(true);

    EXPECT_CALL(parent, draw()).Times(testing::AnyNumber());
    EXPECT_CALL(*child.get(), draw());

    parent.visit(camera, matrix_stack, false);

    testing::Mock::VerifyAndClearExpectations(child.get());

    parent.setPosition(glm::vec2(-100, -100));
    EXPECT_CALL(*child.get(), draw()).Times(0);
    parent.visit(camera, matrix_stack, false);

    testing::Mock::VerifyAndClearExpectations(child.get());

    child->setPosition(glm::vec2(100, 100));
    EXPECT_CALL(*child.get(), draw());
    parent.visit(camera, matrix_stack, false);

    testing::Mock::VerifyAndClearExpectations(child.get());
    parent.setPosition(glm::vec2(50, 50));

    child->setPosition(glm::vec2(60, 0));
    EXPECT_CALL(*child.get(), draw()).Times(0);
    parent.visit(camera, matrix_stack, false);

    testing::Mock::VerifyAndClearExpectations(child.get());
    parent.setPosition(glm::vec2(50, 50));
    parent.setScale(glm::vec2(0.5f, 1.0f));

    child->setPosition(glm::vec2(60, 0));
    EXPECT_CALL(*child.get(), draw());
    parent.visit(camera, matrix_stack, false);

    testing::Mock::VerifyAndClearExpectations(child.get());
    parent.setPosition(glm::vec2(0, 0));
    parent.setScale(glm::vec2(1.0f, 1.0f));

    child->setPosition(glm::vec2(110, 50));
    EXPECT_CALL(*child.get(), draw()).Times(0);
    parent.visit(camera, matrix_stack, false);

    testing::Mock::VerifyAndClearExpectations(child.get());
    child->setRotationQuaternion(glm::angleAxis((float)M_PI, glm::vec3(0, 0, 1)));
    EXPECT_CALL(*child.get(), draw());
    parent.visit(camera, matrix_stack, false);


    FTEngine::cleanup();
}