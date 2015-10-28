#include <Rendering/Textures/FTTextureDDS.h>
#include <glfwmock.h>
#include <FTEngine.h>

#if __cplusplus < 201402L
// no make_unique support
namespace std {
    template<typename T, typename ...Args>
    std::unique_ptr<T> make_unique( Args&& ...args )
    {
            return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
    }
}
#endif

using ::testing::_;
TEST(TestTextureDDS, TestLoadTextureDDS) {
    GlfwMock mock;
    FTEngine::setup(true);


    EXPECT_CALL(mock, gl_GenTextures(1,_));
    EXPECT_CALL(mock,
        gl_CompressedTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 512, 512, 0, _, testing::NotNull()));
    EXPECT_CALL(mock, gl_DeleteTextures(1, _));
    EXPECT_CALL(mock, gl_BindTexture(_, _));
    EXPECT_CALL(mock, gl_PixelStorei(_, _)).WillRepeatedly(testing::Return());

    auto texture = std::make_unique<FTTextureDDS>("Resources/Textures/checker.DDS");
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
    EXPECT_THROW(std::make_unique<FTTextureDDS>("Resources/Fonts/Vera.ttf"), FTException);
    FTEngine::cleanup();
}
