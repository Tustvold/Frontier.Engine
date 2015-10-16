#include <Mock/MockLoader.h>
#include <Rendering/Camera/FTRaycast.h>

TEST(TestRaycast, TestIntersects2D) {
    FTRaycast ray(glm::vec3(50, 70, 0), glm::vec3(0, 0, -1));

    glm::vec2 intersection;

    EXPECT_TRUE(ray.intersectsRect2D(glm::vec2(20, 20), glm::vec2(100, 100), intersection));
    EXPECT_EQ(intersection, glm::vec2(50, 70));

    intersection = glm::vec2(457, 12);

    EXPECT_FALSE(ray.intersectsRect2D(glm::vec2(20, 20), glm::vec2(20, 20), intersection));
    EXPECT_EQ(intersection, glm::vec2(457, 12));

    EXPECT_TRUE(ray.intersectsRect2D(glm::vec2(50, 70), glm::vec2(5, 5), intersection));
    EXPECT_EQ(intersection, glm::vec2(50, 70));

    intersection = glm::vec2(457, 12);

    EXPECT_FALSE(ray.intersectsRect2D(glm::vec2(40, 80), glm::vec2(5, 5), intersection));
    EXPECT_EQ(intersection, glm::vec2(457, 12));
}

TEST(TestRaycast, TestPlaneIntersection) {
    FTRaycast ray(glm::vec3(0, 2, 0), glm::vec3(1, 3, 1));

    // Test Standard
    glm::vec3 intersection;
    EXPECT_TRUE(ray.intersectsPlane(glm::vec3(2,1,-4), glm::vec3(3,2,1), intersection));
    EXPECT_EQ(intersection, glm::vec3(2, 8, 2));

    // Test parrallel no intersection
    intersection = glm::vec3(23, 5, 78);
    FTRaycast ray2(glm::vec3(1, 4, 0), glm::vec3(1, 2, 1));
    EXPECT_FALSE(ray2.intersectsPlane(glm::vec3(2, 1, -4), glm::vec3(3, 2, 1), intersection));
    EXPECT_EQ(intersection, glm::vec3(23, 5, 78));

    // Test parallel with intersection
    FTRaycast ray3(glm::vec3(2, 8, 2), glm::vec3(1, 2, 1));
    EXPECT_TRUE(ray3.intersectsPlane(glm::vec3(2, 1, -4), glm::vec3(3, 2, 1), intersection));
    EXPECT_EQ(intersection, glm::vec3(3,2,1));

}
