#include "gtest/gtest.h"
#include "glm/glm.hpp"
#include <glm/gtx/quaternion.hpp>
#include <Rendering/Scene/Transform/FTTransformUtil.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Frontier.h>

void assertMatrixEqual(const glm::mat4& a, const glm::mat4& b, float epsilon = FLT_EPSILON) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        EXPECT_TRUE(fabsf(a[i][j] - b[i][j]) < epsilon);
}

TEST(TestTransform, TestTranslate) {

    auto transform = std::make_unique<FTTransformPosition>();
    transform->setPosition(glm::vec3(0, 0, 0));

    auto& matrix = transform->getTransformMatrix();

    assertMatrixEqual(matrix, glm::mat4());

    transform->setPosition(glm::vec3(1, -5, 7));

    transform->getTransformMatrix();

    assertMatrixEqual(matrix, glm::mat4(
                          1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          1, -5, 7, 1));

    srand((unsigned int)time(nullptr));

    glm::vec3 pos = glm::vec3(rand() % 100, rand() % 100, rand() % 100);

    transform->setPosition(pos);

    assertMatrixEqual(matrix, glm::mat4(
                          1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          pos.x, pos.y, pos.z, 1));

}

TEST(TestTransform, TestRotate) {
    auto transform = std::make_unique<FTTransformRotation>();
    transform->setRotationQuaterion(glm::quat());

    auto matrix = transform->getTransformMatrix();

    assertMatrixEqual(matrix, glm::mat4());

    transform->setRotationQuaterion(glm::angleAxis(0.0f, glm::vec3(0, 1, 0)));

    matrix = transform->getTransformMatrix();

    assertMatrixEqual(matrix, glm::mat4());

    transform->setRotationQuaterion(glm::angleAxis((float)M_PI, glm::vec3(0, 1, 0)));

    matrix = transform->getTransformMatrix();

    assertMatrixEqual(matrix, glm::mat4(
                          -1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, -1, 0,
                          0, 0, 0, 1));

    transform->setRotationQuaterion(glm::angleAxis((float)(M_PI / 2.0), glm::vec3(1, 0, 0)));

    matrix = transform->getTransformMatrix();

    // Right hand coordinate system and using right hand grip rule
    assertMatrixEqual(matrix, glm::mat4(
                          1, 0, 0, 0,
                          0, 0, 1, 0,
                          0, -1, 0, 0,
                          0, 0, 0, 1));

    transform->setRotationQuaterion(glm::angleAxis((float)(M_PI / 2.0), glm::vec3(0, 0, -1)));

    matrix = transform->getTransformMatrix();

    assertMatrixEqual(matrix, glm::mat4(
                          0, -1, 0, 0,
                          1, 0, 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1));

}

TEST(TestTransform, TestScale) {
    srand((unsigned int)time(nullptr));

    glm::vec3 scale = glm::vec3(rand() % 100, rand() % 100, rand() % 100);
    auto transform = std::make_unique<FTTransformScale>();

    transform->setScale(scale);

    auto& matrix = transform->getTransformMatrix();

    assertMatrixEqual(matrix, glm::mat4(
                          scale.x, 0, 0, 0,
                          0, scale.y, 0, 0,
                          0, 0, scale.z, 0,
                          0, 0, 0, 1));
}

TEST(TestTransform, TestTransformPositionScaleRotation) {
    auto transform = std::make_unique<FTTransformPositionScaleRotation>();
    srand((unsigned int)time(nullptr));

    for (int i = 0; i < 10; i++) {
        glm::vec3 scale = glm::vec3(rand() % 100, rand() % 100, rand() % 100);
        glm::vec3 pos = glm::vec3(rand() % 100, rand() % 100, rand() % 100);
        transform->setPosition(pos);
        transform->setScale(scale);
        transform->setRotationQuaternion(glm::angleAxis((float)(M_PI / 2.0), glm::vec3(0, 0, -1)));

        auto& matrix = transform->getTransformMatrix();

        assertMatrixEqual(matrix, glm::mat4(
                              0, -scale.x, 0, 0,
                              scale.y, 0, 0, 0,
                              0, 0, scale.z, 0,
                              pos.x, pos.y, pos.z, 1), 0.00001f);
    }
}
