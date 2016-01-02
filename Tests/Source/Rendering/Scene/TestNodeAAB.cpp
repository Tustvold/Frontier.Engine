#include <Mock/MockLoader.h>
#include <FTEngine.h>
#include <Rendering/FTShaderNode.h>
#include <Mock/ExpectUtils.h>

TEST(TestNodeAAB, TestAABSimple) {
    MockLoader mock;

    auto node = std::make_shared<FTNode>();
    node->setSize(glm::vec3(34, 88, 22));

    node->visit(glm::mat4(), false);
    node->updateAAB();
    EXPECT_EQ(node->getAABCenter(), glm::vec3(17, 44, 11));
    EXPECT_EQ(node->getAABHalfExtents(), glm::vec3(17, 44, 11));

    node->setPosition(glm::vec3(542, 2, 7));
    node->visit(glm::mat4(), false);

    EXPECT_EQ(node->getAABCenter(), glm::vec3(17 + 542, 44 + 2, 11 + 7.0f));
    EXPECT_EQ(node->getAABHalfExtents(), glm::vec3(17, 44, 11));

    node->setScale(glm::vec3(5, 2, 7));
    node->visit(glm::mat4(), false);

    EXPECT_EQ(node->getAABCenter(), glm::vec3(17*5 + 542, 44*2 + 2, 11*7 + 7.0f));
    EXPECT_EQ(node->getAABHalfExtents(), glm::vec3(17*5, 44*2, 11*7));

    auto quat = glm::angleAxis((float)M_PI_2, glm::vec3(0, 0, 1));
    node->setRotationQuaternion(quat);
    node->visit(glm::mat4(), false);

    EXPECT_EQ(node->getAABCenter(), glm::vec3(542 - 44 * 2, 2+17 * 5, 11 * 7 + 7.0f));
    EXPECT_EQ(node->getAABHalfExtents(), glm::vec3(44 * 2, 17 * 5, 11 * 7));
}

TEST(TestNodeAAB, TestAABAnchorPoint) {
    MockLoader mock;

    auto node = std::make_shared<FTNode>();
    node->setAnchorPoint(glm::vec3(0.3f, 0.5f, 0.7f));
    node->setSize(glm::vec3(34, 88, 22));

    node->visit(glm::mat4(), false);
    expectVectorEqual(node->getAABCenter(), glm::vec3(17 - 0.3f * 34, 0, 11 - 0.7f * 22));
    expectVectorEqual(node->getAABHalfExtents(), glm::vec3(17, 44, 11));

    node->setPosition(glm::vec3(542, 2, 7));
    node->visit(glm::mat4(), false);

    expectVectorEqual(node->getAABCenter(), glm::vec3(17 - 0.3f * 34 + 542, 2, 11 - 0.7f * 22 + 7.0f));
    expectVectorEqual(node->getAABHalfExtents(), glm::vec3(17, 44, 11));

    node->setScale(glm::vec3(5, 2, 7));
    node->visit(glm::mat4(), false);

    expectVectorEqual(node->getAABCenter(), glm::vec3((17 - 0.3f * 34) * 5 + 542, 2, (11 - 0.7f * 22) * 7 + 7.0f), 0.00001f);
    expectVectorEqual(node->getAABHalfExtents(), glm::vec3(17 * 5, 44 * 2, 11 * 7));


    auto quat = glm::angleAxis((float)M_PI_2, glm::vec3(0, 0, 1));
    node->setRotationQuaternion(quat);
    node->visit(glm::mat4(), false);

    expectVectorEqual(node->getAABCenter(), glm::vec3(542, 2 + (17 - 0.3f * 34) * 5, (11 - 0.7f * 22) * 7 + 7.0f), 0.00001f);
    expectVectorEqual(node->getAABHalfExtents(), glm::vec3(44 * 2, 17 * 5, 11 * 7));
}

TEST(TestNodeAAB, TestAABPropogation) {
    MockLoader mock;

    auto child = std::make_shared<FTNode>();
    child->setSize(glm::vec3(4, 6, 8));

    auto parent = std::make_shared<FTNode>();
    parent->addChild(child);

    parent->visit(glm::mat4(), false);
    expectVectorEqual(child->getAABCenter(), glm::vec3(2,3,4));
    expectVectorEqual(child->getAABHalfExtents(), glm::vec3(2,3,4));
    expectVectorEqual(parent->getAABCenter(), glm::vec3(2, 3, 4));
    expectVectorEqual(parent->getAABHalfExtents(), glm::vec3(2, 3, 4));
}

TEST(TestNodeAAB, TestAABPropogationNodeEmpty) {
    MockLoader mock;

    auto child = std::make_shared<FTNode>();
    child->setSize(glm::vec3(4, 6, 8));
    child->setPosition(glm::vec3(12,67,23));

    auto parent = std::make_shared<FTNode>();
    parent->addChild(child);

    parent->visit(glm::mat4(), false);
    expectVectorEqual(child->getAABCenter(), glm::vec3(12 + 2, 67 + 3, 23 + 4));
    expectVectorEqual(child->getAABHalfExtents(), glm::vec3(2, 3, 4));
    expectVectorEqual(child->getAABCenter(), glm::vec3(12 + 2, 67 + 3, 23 + 4));
    expectVectorEqual(parent->getAABHalfExtents(), glm::vec3(2, 3, 4));
}
