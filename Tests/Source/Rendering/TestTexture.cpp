#include "gtest/gtest.h"
#include <Rendering/Textures/FTTextureDDS.h>
#include <glewmock.hpp>
#include <GL/glew.h>




using ::testing::_;
TEST(TestTexture, TestLoadTextureDDS) {
	/*GlewMock mock;
	EXPECT_CALL(mock, gl_GenTextures(1,_));
	EXPECT_CALL(mock, 
		gl_CompressedTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 512, 512, 0, _, testing::NotNull()));
	EXPECT_CALL(mock, gl_DeleteTextures(1, _));
	EXPECT_CALL(mock, gl_BindTexture(_, _));
	EXPECT_CALL(mock, gl_PixelStorei(_, _)).WillRepeatedly(testing::Return());

	auto texture = new FTTextureDDS("Resources/Textures/checker.DDS");
	EXPECT_EQ(texture->getWidth(), 512);
	EXPECT_EQ(texture->getHeight(), 512);
	EXPECT_EQ(texture->getMipMapCount(), 1);
	delete texture;*/
}