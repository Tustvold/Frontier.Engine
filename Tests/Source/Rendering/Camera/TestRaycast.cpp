#include <Mock/MockLoader.h>
#include <Rendering/Camera/FTRaycast.h>
#include <Mock/ExpectUtils.h>

TEST(TestRaycast, TestPlaneIntersection) {
    FTRaycast ray(glm::vec3(0, 2, 0), glm::vec3(1, 3, 1));

    // Test Standard
    glm::vec3 intersection;
    EXPECT_TRUE(ray.intersectsPlane(glm::vec3(2,1,-4), glm::vec3(3,2,1), intersection));
    expectVectorEqual(intersection, glm::vec3(2, 8, 2));

    // Test parrallel no intersection
    intersection = glm::vec3(23, 5, 78);
    FTRaycast ray2(glm::vec3(1, 4, 0), glm::vec3(1, 2, 1));
    EXPECT_FALSE(ray2.intersectsPlane(glm::vec3(2, 1, -4), glm::vec3(3, 2, 1), intersection));
    expectVectorEqual(intersection, glm::vec3(23, 5, 78));

    // Test parallel with intersection
    FTRaycast ray3(glm::vec3(2, 8, 2), glm::vec3(1, 2, 1));
    EXPECT_TRUE(ray3.intersectsPlane(glm::vec3(2, 1, -4), glm::vec3(3, 2, 1), intersection));
    expectVectorEqual(intersection, glm::vec3(3, 2, 1));

}


TEST(TestRaycast, TestSphereIntersection) {
    FTRaycast ray(glm::vec3(0, 0, -5), glm::vec3(0, 0, 1));
    glm::vec3 intersection;
    float distance;
    EXPECT_TRUE(ray.intersectsSphere(glm::vec3(0, 0, 0), 4, intersection, distance));
    expectVectorEqual(intersection, glm::vec3(0, 0, -2));
    EXPECT_EQ(distance, 3);

    EXPECT_TRUE(ray.intersectsSphere(glm::vec3(0, 2, 0), 4, intersection, distance));
    expectVectorEqual(intersection, glm::vec3(0, 0, 0));
    EXPECT_EQ(distance, 5);

    EXPECT_FALSE(ray.intersectsSphere(glm::vec3(0, 2.5, 0), 4, intersection, distance));
    expectVectorEqual(intersection, glm::vec3(0, 0, 0));
    EXPECT_EQ(distance, 5);

    FTRaycast ray2(glm::vec3(5, 5, 0), glm::vec3(-1, -1, 0));
    EXPECT_TRUE(ray2.intersectsSphere(glm::vec3(0, 0, 0), 4, intersection, distance));

    glm::vec3 expectedIntersection = glm::normalize(glm::vec3(1,1,0))*2.0f;
    expectVectorEqual(intersection, expectedIntersection);
    expectFuzzyEq(distance, glm::length(glm::vec3(5, 5, 0)) - glm::length(expectedIntersection));
}