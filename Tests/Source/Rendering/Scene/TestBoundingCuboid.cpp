#include <Mock/MockLoader.h>
#include <Engine.h>
#include <Rendering/ShaderNode.h>
#include <Mock/ExpectUtils.h>
#include <Rendering/BoundingShape/BoundingCuboid.h>

USING_NS_FT

TEST(TestBoundingCuboid, TestAABSimple) {
    MockLoader mock;

    auto node = std::make_shared<Node>();
    auto bounding_shape = new BoundingCuboid(glm::vec3(), glm::vec3(34, 88, 22));
    node->setBoundingShape(std::unique_ptr<BoundingShape>(bounding_shape));

    node->visit(glm::mat4(), false);
    EXPECT_EQ(bounding_shape->getAABCenter(), glm::vec3(17, 44, 11));
    EXPECT_EQ(bounding_shape->getAABHalfExtents(), glm::vec3(17, 44, 11));

    node->setPosition(glm::vec3(542, 2, 7));
    node->visit(glm::mat4(), false);

    EXPECT_EQ(bounding_shape->getAABCenter(), glm::vec3(17 + 542, 44 + 2, 11 + 7.0f));
    EXPECT_EQ(bounding_shape->getAABHalfExtents(), glm::vec3(17, 44, 11));

    node->setScale(glm::vec3(5, 2, 7));
    node->visit(glm::mat4(), false);

    EXPECT_EQ(bounding_shape->getAABCenter(), glm::vec3(17*5 + 542, 44*2 + 2, 11*7 + 7.0f));
    EXPECT_EQ(bounding_shape->getAABHalfExtents(), glm::vec3(17*5, 44*2, 11*7));

    auto quat = glm::angleAxis((float)M_PI_2, glm::vec3(0, 0, 1));
    node->setRotationQuaternion(quat);
    node->visit(glm::mat4(), false);

    EXPECT_EQ(bounding_shape->getAABCenter(), glm::vec3(542 - 44 * 2, 2+17 * 5, 11 * 7 + 7.0f));
    EXPECT_EQ(bounding_shape->getAABHalfExtents(), glm::vec3(44 * 2, 17 * 5, 11 * 7));
}

TEST(TestBoundingCuboid, TestAABAnchorPoint) {
    MockLoader mock;

    auto node = std::make_shared<Node>();
    auto bounding_shape = new BoundingCuboid(glm::vec3(), glm::vec3(34, 88, 22));
    node->setBoundingShape(std::unique_ptr<BoundingShape>(bounding_shape));

    node->setAnchorPoint(glm::vec3(0.3f, 0.5f, 0.7f));

    node->visit(glm::mat4(), false);

    expectVectorEqual(bounding_shape->getAABCenter(), glm::vec3(17 - 0.3f * 34, 0, 11 - 0.7f * 22));
    expectVectorEqual(bounding_shape->getAABHalfExtents(), glm::vec3(17, 44, 11));

    node->setPosition(glm::vec3(542, 2, 7));
    node->visit(glm::mat4(), false);

    expectVectorEqual(bounding_shape->getAABCenter(), glm::vec3(17 - 0.3f * 34 + 542, 2, 11 - 0.7f * 22 + 7.0f));
    expectVectorEqual(bounding_shape->getAABHalfExtents(), glm::vec3(17, 44, 11));

    node->setScale(glm::vec3(5, 2, 7));
    node->visit(glm::mat4(), false);

    expectVectorEqual(bounding_shape->getAABCenter(), glm::vec3((17 - 0.3f * 34) * 5 + 542, 2, (11 - 0.7f * 22) * 7 + 7.0f));
    expectVectorEqual(bounding_shape->getAABHalfExtents(), glm::vec3(17 * 5, 44 * 2, 11 * 7));


    auto quat = glm::angleAxis((float)M_PI_2, glm::vec3(0, 0, 1));
    node->setRotationQuaternion(quat);
    node->visit(glm::mat4(), false);

    expectVectorEqual(bounding_shape->getAABCenter(), glm::vec3(542, 2 + (17 - 0.3f * 34) * 5, (11 - 0.7f * 22) * 7 + 7.0f));
    expectVectorEqual(bounding_shape->getAABHalfExtents(), glm::vec3(44 * 2, 17 * 5, 11 * 7));
}