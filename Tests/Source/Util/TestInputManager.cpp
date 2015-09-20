#include <glfwmock.h>
#include <FTEngine.h>
#include <Util/FTInputManager.h>
#include <Mock/MockEngineEventDispatcher.h>

TEST(TestInputManager, TestKeyStatePressed) {
    GlfwMock mock;
    FTEngine::setup(true);

    auto state = FTEngine::getInputManager()->getKeyState("Forward", GLFW_KEY_0);

    EXPECT_FALSE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_0, 23, GLFW_PRESS, 0);

    EXPECT_TRUE(state->isPressed());

    FTEngine::cleanup();
}

TEST(TestInputManager, TestKeyStateReleased) {
    GlfwMock mock;
    FTEngine::init();
    auto engine_event_dispatcher = std::make_shared<MockEngineEventDispatcher>();
    FTEngine::getEventManager()->registerDispatcher(std::static_pointer_cast<FTEngineEventDispatcher>(engine_event_dispatcher));
    FTEngine::setup(true);

    auto state = FTEngine::getInputManager()->getKeyState("Forward", GLFW_KEY_0);

    EXPECT_FALSE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_0, 23, GLFW_PRESS, 0);

    EXPECT_TRUE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_0, 23, GLFW_RELEASE, 0);

    // We don't expect the state to get updated until the next world tick
    EXPECT_TRUE(state->isPressed());

    engine_event_dispatcher->raiseEvent(FTPreDrawEvent(1.0, 60.0));

    EXPECT_FALSE(state->isPressed());

    FTEngine::cleanup();
}

TEST(TestInputManager, TestMapKey) {
    GlfwMock mock;
    FTEngine::init();
    auto engine_event_dispatcher = std::make_shared<MockEngineEventDispatcher>();
    FTEngine::getEventManager()->registerDispatcher(std::static_pointer_cast<FTEngineEventDispatcher>(engine_event_dispatcher));
    FTEngine::setup(true);

    auto state = FTEngine::getInputManager()->getKeyState("Forward");
    FTEngine::getInputManager()->addMapping("Forward", GLFW_KEY_0);

    EXPECT_FALSE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_0, 23, GLFW_PRESS, 0);

    EXPECT_TRUE(state->isPressed());

    mock.key_callback_(nullptr, GLFW_KEY_0, 23, GLFW_RELEASE, 0);

    // We don't expect the state to get updated until the next world tick
    EXPECT_TRUE(state->isPressed());

    engine_event_dispatcher->raiseEvent(FTPreDrawEvent(1.0, 60.0));

    EXPECT_FALSE(state->isPressed());

    FTEngine::cleanup();
}
