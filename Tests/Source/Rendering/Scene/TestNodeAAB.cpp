#include <glfwmock.h>
#include <FTEngine.h>
#include <Rendering/Scene/FTNode.h>
#include <Mock/MockShader.h>
#include <Mock/ExpectUtils.h>

TEST(TestNodeAAB, TestAABSimple) {
    GlfwMock mock;
    FTEngine::setup(true);

    auto node = std::make_shared<FTNode<MockShader>>();
    node->setSize(glm::vec3(34, 88, 22));

    node->updateMatrices();
    node->updateAAB(node->getTransformMatrix());
    EXPECT_EQ(node->getAABCenter(), glm::vec3(17, 44, 11));
    EXPECT_EQ(node->getAABHalfExtents(), glm::vec3(17, 44, 11));

    node->setPosition(glm::vec3(542, 2, 7));
    node->updateMatrices();
    node->updateAAB(node->getTransformMatrix());
    
    EXPECT_EQ(node->getAABCenter(), glm::vec3(17 + 542, 44 + 2, 11 + 7.0f));
    EXPECT_EQ(node->getAABHalfExtents(), glm::vec3(17, 44, 11));

    node->setScale(glm::vec3(5, 2, 7));
    node->updateMatrices();
    node->updateAAB(node->getTransformMatrix());

    EXPECT_EQ(node->getAABCenter(), glm::vec3(17*5 + 542, 44*2 + 2, 11*7 + 7.0f));
    EXPECT_EQ(node->getAABHalfExtents(), glm::vec3(17*5, 44*2, 11*7));

    auto quat = glm::angleAxis((float)M_PI_2, glm::vec3(0, 0, 1));
    node->setRotationQuaternion(quat);
    node->updateMatrices();
    node->updateAAB(node->getTransformMatrix());

    EXPECT_EQ(node->getAABCenter(), glm::vec3(542 - 44 * 2, 2+17 * 5, 11 * 7 + 7.0f));
    EXPECT_EQ(node->getAABHalfExtents(), glm::vec3(44 * 2, 17 * 5, 11 * 7));

    FTEngine::cleanup();
}

TEST(TestNodeAAB, TestAABAnchorPoint) {
    GlfwMock mock;
    FTEngine::setup(true);

    auto node = std::make_shared<FTNode<MockShader>>();
    node->setAnchorPoint(glm::vec3(0.3f, 0.5f, 0.7f));
    node->setSize(glm::vec3(34, 88, 22));

    node->updateMatrices();
    node->updateAAB(node->getTransformMatrix());
    expectVectorEqual(node->getAABCenter(), glm::vec3(17 - 0.3f * 34, 0, 11 - 0.7f * 22));
    expectVectorEqual(node->getAABHalfExtents(), glm::vec3(17, 44, 11));

    node->setPosition(glm::vec3(542, 2, 7));
    node->updateMatrices();
    node->updateAAB(node->getTransformMatrix());

    expectVectorEqual(node->getAABCenter(), glm::vec3(17 - 0.3f * 34 + 542, 2, 11 - 0.7f * 22 + 7.0f));
    expectVectorEqual(node->getAABHalfExtents(), glm::vec3(17, 44, 11));

    node->setScale(glm::vec3(5, 2, 7));
    node->updateMatrices();
    node->updateAAB(node->getTransformMatrix());

    expectVectorEqual(node->getAABCenter(), glm::vec3((17 - 0.3f * 34) * 5 + 542, 2, (11 - 0.7f * 22) * 7 + 7.0f), 0.00001f);
    expectVectorEqual(node->getAABHalfExtents(), glm::vec3(17 * 5, 44 * 2, 11 * 7));
    

    auto quat = glm::angleAxis((float)M_PI_2, glm::vec3(0, 0, 1));
    node->setRotationQuaternion(quat);
    node->updateMatrices();
    node->updateAAB(node->getTransformMatrix());

    expectVectorEqual(node->getAABCenter(), glm::vec3(542, 2 + (17 - 0.3f * 34) * 5, (11 - 0.7f * 22) * 7 + 7.0f), 0.00001f);
    expectVectorEqual(node->getAABHalfExtents(), glm::vec3(44 * 2, 17 * 5, 11 * 7));

    FTEngine::cleanup();
}