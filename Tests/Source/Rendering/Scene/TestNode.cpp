#include <Mock/MockLoader.h>
#include <FTEngine.h>
#include <Rendering/FTShaderNode.h>
#include <Mock/MockShader.h>
#include <Mock/ExpectUtils.h>
#include <Rendering/Camera/FTCamera2D.h>
#include <Rendering/FTView.h>
#include <Rendering/FTScene.h>

class MockNodeDraw : public FTNode {

public:

    MOCK_METHOD1(pre_draw, void(const glm::mat4&));
    MOCK_METHOD0(draw, void());
    MOCK_METHOD0(post_draw, void());
    MOCK_METHOD1(onAddedToView, void(FTView* view));
    MOCK_METHOD1(onAddedToScene, void(FTScene* scene));

    void callParentAddedToView(FTView* view) {
        FTNode::onAddedToView(view);
    }

    void callParentAddedToScene(FTScene* scene) {
        FTNode::onAddedToScene(scene);
    }
};

class MockNodeChildren : public FTNode {
public:

    MOCK_METHOD0(draw, void());
};


TEST(TestNode, TestCallOrder) {
    MockLoader mock;

    auto camera = std::static_pointer_cast<FTCamera>(std::make_shared<FTCamera2D>());
    auto screensize = FTEngine::getWindowSize();
    camera->setDrawRectRelative(FTRect<float>(0, 0, 100.0f / screensize.x, 100.0f / screensize.y));
    glm::mat4 parent_matrix;
    MockNodeDraw node;

    testing::InSequence s;
    EXPECT_CALL(node, pre_draw(testing::_));
    EXPECT_CALL(node, draw());
    EXPECT_CALL(node, post_draw());

    node.visit(parent_matrix, false);
    node.performDraw(camera.get());

}


TEST(TestNode, TestCulling) {
    MockLoader loader;

    auto camera = std::static_pointer_cast<FTCamera>(std::make_shared<FTCamera2D>());

    auto screensize = FTEngine::getWindowSize();
    camera->setDrawRectRelative(FTRect<float>(0, 0, 100.0f / screensize.x, 100.0f / screensize.y));
    glm::mat4 parent_matrix;
    MockNodeChildren node;
    node.setSize(glm::vec2(50, 80));

    EXPECT_CALL(node, draw());

    node.visit(parent_matrix, false);
    node.performDraw(camera.get());


    testing::Mock::VerifyAndClearExpectations(&node);

    EXPECT_CALL(node, draw()).Times(0);

    node.setPosition(glm::vec2(-55, -85));

    node.visit(parent_matrix, false);
    node.performDraw(camera.get());


    testing::Mock::VerifyAndClearExpectations(&node);

    EXPECT_CALL(node, draw()).Times(0);

    node.setPosition(glm::vec2(-0.1f, -0.1f));
    node.setAnchorPoint(glm::vec2(1.0f, 0.0f));

    node.visit(parent_matrix, false);
    node.performDraw(camera.get());

    testing::Mock::VerifyAndClearExpectations(&node);

    EXPECT_CALL(node, draw()).Times(0);

    node.setPosition(glm::vec2(100.1f, 0.0f));
    node.setAnchorPoint(glm::vec2(0.0f, 0.0f));

    node.visit(parent_matrix, false);
    node.performDraw(camera.get());

    testing::Mock::VerifyAndClearExpectations(&node);


    EXPECT_CALL(node, draw());

    node.setRotationQuaternion(glm::angleAxis((float)M_PI, glm::vec3(0, 0, 1)));

    node.visit(parent_matrix, false);
    node.performDraw(camera.get());

}

TEST(TestNode, TestCullingHierarchy) {
    MockLoader mock;

    auto camera = std::static_pointer_cast<FTCamera>(std::make_shared<FTCamera2D>());
    auto screensize = FTEngine::getWindowSize();
    camera->setDrawRectRelative(FTRect<float>(0, 0, 100.0f / screensize.x, 100.0f / screensize.y));
    glm::mat4 parent_matrix;
    MockNodeChildren parent;
    auto child = std::make_shared<MockNodeChildren>();
    parent.addChild(std::static_pointer_cast<FTNode>(child));
    child->setSize(glm::vec2(50, 80));

    EXPECT_CALL(parent, draw()).Times(testing::AnyNumber());
    EXPECT_CALL(*child.get(), draw());

    parent.visit(parent_matrix, false);
    parent.performDraw(camera.get());

    testing::Mock::VerifyAndClearExpectations(child.get());

    parent.setPosition(glm::vec2(-100, -100));
    EXPECT_CALL(*child.get(), draw()).Times(0);
    parent.visit(parent_matrix, false);
    parent.performDraw(camera.get());

    testing::Mock::VerifyAndClearExpectations(child.get());

    child->setPosition(glm::vec2(100, 100));
    EXPECT_CALL(*child.get(), draw());
    parent.visit(parent_matrix, false);
    parent.performDraw(camera.get());

    testing::Mock::VerifyAndClearExpectations(child.get());
    parent.setPosition(glm::vec2(50, 50));

    child->setPosition(glm::vec2(60, 0));
    EXPECT_CALL(*child.get(), draw()).Times(0);
    parent.visit(parent_matrix, false);
    parent.performDraw(camera.get());

    testing::Mock::VerifyAndClearExpectations(child.get());
    parent.setPosition(glm::vec2(50, 50));
    parent.setScale(glm::vec2(0.5f, 1.0f));

    child->setPosition(glm::vec2(60, 0));
    EXPECT_CALL(*child.get(), draw());
    parent.visit(parent_matrix, false);
    parent.performDraw(camera.get());

    testing::Mock::VerifyAndClearExpectations(child.get());
    parent.setPosition(glm::vec2(0, 0));
    parent.setScale(glm::vec2(1.0f, 1.0f));

    child->setPosition(glm::vec2(110, 50));
    EXPECT_CALL(*child.get(), draw()).Times(0);
    parent.visit(parent_matrix, false);
    parent.performDraw(camera.get());

    testing::Mock::VerifyAndClearExpectations(child.get());
    child->setRotationQuaternion(glm::angleAxis((float)M_PI, glm::vec3(0, 0, 1)));
    EXPECT_CALL(*child.get(), draw());
    parent.visit(parent_matrix, false);
    parent.performDraw(camera.get());

}

TEST(TestNode, TestOnAddedToParent) {
    MockLoader loader;

    auto scene = std::make_shared<FTScene>();
    auto view = std::make_shared<FTView>();
    scene->addView(view);

    auto node1 = std::make_shared<MockNodeDraw>();
    auto node2 = std::make_shared<MockNodeDraw>();
    auto node3 = std::make_shared<MockNodeDraw>();

    EXPECT_CALL(*node1, onAddedToView(view.get())).Times(0);
    EXPECT_CALL(*node2, onAddedToView(view.get())).Times(0);
    EXPECT_CALL(*node3, onAddedToView(view.get())).Times(0);

    node2->addChild(node3);
    node1->addChild(node2);

    testing::Mock::VerifyAndClearExpectations(node1.get());
    testing::Mock::VerifyAndClearExpectations(node2.get());
    testing::Mock::VerifyAndClearExpectations(node3.get());

    testing::Sequence s1;
    testing::Sequence s2;
    testing::Sequence s3;

    EXPECT_CALL(*node1, onAddedToView(view.get())).InSequence(s1).WillOnce(testing::Invoke(node1.get(), &MockNodeDraw::callParentAddedToView));
    EXPECT_CALL(*node2, onAddedToView(view.get())).InSequence(s2).WillOnce(testing::Invoke(node2.get(), &MockNodeDraw::callParentAddedToView));
    EXPECT_CALL(*node3, onAddedToView(view.get())).InSequence(s3).WillOnce(testing::Invoke(node3.get(), &MockNodeDraw::callParentAddedToView));

    EXPECT_CALL(*node1, onAddedToScene(scene.get())).InSequence(s1).WillOnce(testing::Invoke(node1.get(), &MockNodeDraw::callParentAddedToScene));
    EXPECT_CALL(*node2, onAddedToScene(scene.get())).InSequence(s2).WillOnce(testing::Invoke(node2.get(), &MockNodeDraw::callParentAddedToScene));
    EXPECT_CALL(*node3, onAddedToScene(scene.get())).InSequence(s3).WillOnce(testing::Invoke(node3.get(), &MockNodeDraw::callParentAddedToScene));

    view->addChild(node1);
}