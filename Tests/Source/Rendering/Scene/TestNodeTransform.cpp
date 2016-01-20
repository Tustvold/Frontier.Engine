#include <Mock/MockLoader.h>
#include <FTEngine.h>
#include <Rendering/FTShaderNode.h>
#include <Mock/ExpectUtils.h>
#include <Rendering/BoundingShape/FTBoundingCuboid.h>

class MockNodeTransform : public FTNode {
public:
    std::unique_ptr<FTTransformScale>& getScaleTransform() {
        return scale_transform_;
    }

    std::unique_ptr<FTTransformPosition>& getPositionTransform() {
        return position_transform_;
    }

    std::unique_ptr<FTTransformRotation>& getRotationTransform() {
        return rotation_transform_;
    }
};

TEST(TestNodeTransform, TestGetSet) {
    MockLoader mock;

    auto node = std::make_shared<FTNode>();

    node->setPosition(glm::vec3(1, 5, 21));
    EXPECT_EQ(node->getPosition(), glm::vec3(1, 5, 21));

    node->setPosition(glm::vec2(3, 8));
    EXPECT_EQ(node->getPosition(), glm::vec3(3, 8, 0));

    node->setScale(glm::vec3(1, 5, 21));
    EXPECT_EQ(node->getScale(), glm::vec3(1, 5, 21));

    node->setScale(glm::vec2(3, 8));
    EXPECT_EQ(node->getScale(), glm::vec3(3, 8, 1));

    auto quat = glm::angleAxis(0.0f, glm::vec3(0, 0, 1));
    node->setRotationQuaternion(quat);
    EXPECT_EQ(node->getRotationQuaternion(), quat);
}

TEST(TestNodeTransform, TestTransform) {
    MockLoader mock;

    auto node = std::make_shared<MockNodeTransform>();

    expectMatrixEqual(node->getPositionTransform()->getTransformMatrix(), glm::mat4());
    node->setPosition(glm::vec3(5, 3, 9));
    node->setScale(glm::vec3(2, 6, 9));
    auto quat = glm::angleAxis((float)M_PI_2, glm::vec3(0, 0, 1));
    node->setRotationQuaternion(quat);
    node->visit(glm::mat4(), false);

    auto expectedPosition = glm::mat4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        5, 3, 9, 1
    );

    auto expectedRotation = glm::mat4(
        0, 1, 0, 0,
        -1, 0, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );

    auto expectedScale = glm::mat4(
        2, 0, 0, 0,
        0, 6, 0, 0,
        0, 0, 9, 0,
        0, 0, 0, 1
    );

    expectMatrixEqual(node->getPositionTransform()->getTransformMatrix(), expectedPosition);

    expectMatrixEqual(node->getRotationTransform()->getTransformMatrix(), expectedRotation, 0.0001f);

    expectMatrixEqual(node->getScaleTransform()->getTransformMatrix(), expectedScale);

    expectMatrixEqual(node->getTransformMatrix(), expectedPosition * expectedRotation * expectedScale, 0.0001f);
}

TEST(TestNodeTransform, TestAnchorPointSimple) {
    MockLoader mock;

    auto node = std::make_shared<MockNodeTransform>();

    expectMatrixEqual(node->getPositionTransform()->getTransformMatrix(), glm::mat4());
    node->setPosition(glm::vec3(5, 3, 9));
    node->setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(48, 24, 96)));
    node->setAnchorPoint(glm::vec3(0.25f, 0.75f, 0.3f));
    node->visit(glm::mat4(), false);

    auto expectedPosition = glm::mat4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        5 - 0.25f * 48.0f, 3 - 24 * 0.75f, 9 - 96 * 0.3f, 1
    );

    expectMatrixEqual(node->getModelMatrix(), expectedPosition);
}

TEST(TestNodeTransform, TestAnchorPointScale) {
    MockLoader mock;

    auto node = std::make_shared<MockNodeTransform>();

    expectMatrixEqual(node->getPositionTransform()->getTransformMatrix(), glm::mat4());
    node->setPosition(glm::vec3(5, 3, 9));
    node->setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(48, 24, 96)));
    node->setScale(glm::vec3(56, 3, 9));
    node->setAnchorPoint(glm::vec3(0.25f, 0.75f, 0.3f));
    node->visit(glm::mat4(), false);

    auto expectedPosition = glm::mat4(
        56, 0, 0, 0,
        0, 3, 0, 0,
        0, 0, 9, 0,
        5 - 0.25f * 48.0f * 56, 3 - 24 * 0.75f * 3, 9 - 96 * 0.3f * 9, 1
    );

    expectMatrixEqual(node->getModelMatrix(), expectedPosition);
}

TEST(TestNodeTransform, TestAnchorPointRotate) {
    MockLoader mock;

    auto node = std::make_shared<MockNodeTransform>();

    expectMatrixEqual(node->getPositionTransform()->getTransformMatrix(), glm::mat4());
    node->setPosition(glm::vec3(5, 3, 9));
    node->setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(48, 24, 96)));
    node->setScale(glm::vec3(56, 3, 9));
    auto quat = glm::angleAxis((float)M_PI_2, glm::vec3(0, 0, 1));

    node->setRotationQuaternion(quat);
    node->setAnchorPoint(glm::vec3(0.25f, 0.75f, 0.3f));
    node->visit(glm::mat4(), false);

    auto expectedPosition =  
        glm::mat4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        5 + 24 * 0.75f * 3, 3 - 0.25f * 48.0f * 56, 9 - 96 * 0.3f * 9, 1
    ) * glm::toMat4(quat) * glm::mat4(
        56, 0, 0, 0,
        0, 3, 0, 0,
        0, 0, 9, 0,
        0, 0, 0, 1
        );

    expectMatrixEqual(node->getModelMatrix(), expectedPosition, 0.0001f);
}
