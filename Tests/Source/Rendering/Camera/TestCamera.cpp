#include <Frontier.h>
#include <glfwmock.h>
#include <Rendering/Camera/Camera.h>
#include <Rendering/Camera/Camera2D.h>
#include <Rendering/Camera/Camera3D.h>
#include <Mock/ExpectUtils.h>

USING_NS_FT

TEST(TestCamera, TestRaycast2D) {
    GlfwMock mock;
    Engine::setup(true, true); {
        auto camera = std::make_unique<Camera2D>();

        // Call this to update matrices
        camera->visit();

        auto raycast = camera->generateRaycastForMousePos(50, 123);
        auto near_vector = raycast.getOrigin();
        auto direction = raycast.getDirection();

        EXPECT_EQ(near_vector, glm::vec3(50, 123, 0));
        EXPECT_EQ(direction, glm::vec3(0, 0, -1.0f));
    }
    Engine::cleanup();
}


TEST(TestCamera, TestRaycast2DDrawRect) {
    GlfwMock mock;
    Engine::setup(true, true); {
        auto camera = std::make_unique<Camera2D>();
        camera->setDrawRectRelative(Rect<float>(0.25f, 0.25f, 0.75f, 0.75f));

        // Call this to update matrices
        auto screensize = Engine::getWindowSize();

        camera->visit();

        auto raycast = camera->generateRaycastForMousePos(0.25f* screensize.x, 0.25f*screensize.y);
        auto near_vector = raycast.getOrigin();
        auto direction = raycast.getDirection();

        EXPECT_EQ(near_vector, glm::vec3(0, 0, 0));
        EXPECT_EQ(direction, glm::vec3(0, 0, -1.0f));

        raycast = camera->generateRaycastForMousePos(0.25f* screensize.x + 20, 0.25f*screensize.y + 40);
        near_vector = raycast.getOrigin();
        direction = raycast.getDirection();

        EXPECT_EQ(near_vector, glm::vec3(20, 40, 0));
        EXPECT_EQ(direction, glm::vec3(0, 0, -1.0f));    
    }
    Engine::cleanup();
}


TEST(TestCamera, TestRaycast3D) {
    GlfwMock mock;
    Engine::setup(true, true); {

        auto camera = std::make_unique<Camera3D>();
        camera->setClippingPlanes(1.0f, 10.0f);
        camera->setFov((float)M_PI_2);
        camera->setPosition(glm::vec3(50, 30, 20));


        // Call this to update matrices

        auto screensize = Engine::getWindowSize();
        camera->visit();

        auto raycast = camera->generateRaycastForMousePos(screensize.x / 2.0f, screensize.y / 2.0f);
        auto origin = raycast.getOrigin();
        auto direction = raycast.getDirection();

        expectVectorEqual(origin, glm::vec3(50, 30, 20));
        expectVectorEqual(direction, glm::vec3(0, 0, -1));

        raycast = camera->generateRaycastForMousePos(screensize.x / 2.0f, screensize.y / 2.0f + 20);
        origin = raycast.getOrigin();
        direction = raycast.getDirection();

        expectVectorEqual(origin, glm::vec3(50, 30, 20));
        expectFuzzyEq(direction.x, 0.0f);
        EXPECT_TRUE(direction.y > 0.0f);

        raycast = camera->generateRaycastForMousePos(0, screensize.y / 2.0f);
        origin = raycast.getOrigin();
        direction = raycast.getDirection();

        auto aspect = (float)screensize.x / (float)screensize.y;

        expectVectorEqual(origin, glm::vec3(50, 30, 20));
        glm::vec3 delta = glm::normalize(glm::vec3(-9.0f * tanf(45.0f * DEG2RAD) * aspect, 0, -9));
        expectVectorEqual(direction, delta);
    }
    Engine::cleanup();
}
