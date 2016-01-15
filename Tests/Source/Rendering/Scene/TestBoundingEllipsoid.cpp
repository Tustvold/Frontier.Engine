#include <Mock/MockLoader.h>
#include <FTEngine.h>
#include <Rendering/FTShaderNode.h>
#include <Mock/ExpectUtils.h>
#include <Rendering/BoundingShape/FTBoundingEllipsoid.h>

TEST(TestBoundingEllipsoid, TestAAB) {
    MockLoader mock;

    auto node = std::make_shared<FTNode>();
    auto bounding_shape = std::make_shared<FTBoundingEllipsoid>(glm::vec3(17, 44, 11));
    node->setBoundingShape(bounding_shape);

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
}


TEST(TestBoundingEllipsoid, TestShapeSimple) {
    auto bounding_shape = std::make_shared<FTBoundingEllipsoid>(glm::vec3(17, 44, 11));

    EXPECT_TRUE(bounding_shape->containsLocalPosition(glm::vec3(17, 44, 11)));
    
    EXPECT_TRUE(bounding_shape->containsLocalPosition(glm::vec3(17*2.0f, 44, 11)));
    EXPECT_TRUE(bounding_shape->containsLocalPosition(glm::vec3(17, 44*2.0f, 11)));
    EXPECT_TRUE(bounding_shape->containsLocalPosition(glm::vec3(17, 44, 11*2.0f)));
    EXPECT_TRUE(bounding_shape->containsLocalPosition(glm::vec3(0, 44, 11)));
    EXPECT_TRUE(bounding_shape->containsLocalPosition(glm::vec3(17, 0, 11)));
    EXPECT_TRUE(bounding_shape->containsLocalPosition(glm::vec3(17, 44, 0)));

    EXPECT_FALSE(bounding_shape->containsLocalPosition(glm::vec3(17 * 2.0f+1.0f, 44, 11)));
    EXPECT_FALSE(bounding_shape->containsLocalPosition(glm::vec3(17, 44 * 2.0f+ 1.0f, 11)));
    EXPECT_FALSE(bounding_shape->containsLocalPosition(glm::vec3(17, 44, 11 * 2.0f+ 1.0f)));
    EXPECT_FALSE(bounding_shape->containsLocalPosition(glm::vec3(-1.0f, 44, 11)));
    EXPECT_FALSE(bounding_shape->containsLocalPosition(glm::vec3(17, -1.0f, 11)));
    EXPECT_FALSE(bounding_shape->containsLocalPosition(glm::vec3(17, 44, -1.0f)));

    EXPECT_FALSE(bounding_shape->containsLocalPosition(glm::vec3(17 * 2.0f, 44+1.0f, 11)));
    EXPECT_FALSE(bounding_shape->containsLocalPosition(glm::vec3(17, 44 * 2.0f, 11+ 1.0f)));
    EXPECT_FALSE(bounding_shape->containsLocalPosition(glm::vec3(17+ 1.0f, 44, 11 * 2.0f)));
    EXPECT_FALSE(bounding_shape->containsLocalPosition(glm::vec3(0, 44+ 1.0f, 11)));
    EXPECT_FALSE(bounding_shape->containsLocalPosition(glm::vec3(17, 0, 11+ 1.0f)));
    EXPECT_FALSE(bounding_shape->containsLocalPosition(glm::vec3(17+ 1.0f, 44, 0)));
}

