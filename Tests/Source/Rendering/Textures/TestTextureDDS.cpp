#include <Rendering/Textures/FTTextureDDS.h>
#include <glfwmock.h>
#include <FTEngine.h>
#include <gmock/gmock.h>

using ::testing::_;
TEST(TestTextureDDS, TestLoadTextureDDS) {
    GlfwMock mock;
    FTEngine::setup(true);

    auto texture = std::make_unique<FTTextureDDS>("TestResources/Textures/checker.DDS");
    EXPECT_EQ(texture->getWidth(), 512);
    EXPECT_EQ(texture->getHeight(), 512);
    EXPECT_EQ(texture->getMipMapCount(), 1);

    FTEngine::cleanup();
}

TEST(TestTextureDDS, TestAssertions) {

    GlfwMock mock;
    FTEngine::setup(true);

    // Test fails gracefully when called with non-existent file
    EXPECT_THROW(std::make_unique<FTTextureDDS>("This is not a file"), FTException);
    // Test fails gracefully when called with a non DDS file
    EXPECT_THROW(std::make_unique<FTTextureDDS>("TestResources/Fonts/Vera.ttf"), FTException);
    FTEngine::cleanup();
}
