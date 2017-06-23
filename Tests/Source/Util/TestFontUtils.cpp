#include <gtest/gtest.h>
#include "Rendering/Text/FontUtils.h"
#include "Rendering/Text/Font.h"
#include "Mock/MockLoader.h"
#include<IO/FileManager.h>

USING_NS_FT

TEST(TestFontUtils, FTFontFile) {
    MockLoader mock;
    auto font = std::make_shared<Font>("TestResources/Fonts/Vera.ttf");

    ttvfs::File *file = Engine::getFileManager()->getOrCreateFile("TestResources/Vera.ftfont");
    file->open("wb");
    FontUtils::serializeFont(font->getTextureFont(), file);
    file->close();

    auto font_test = std::make_shared<Font>("TestResources/Vera.ftfont");
    font_test.reset();
}

TEST(TestFontUtils, Serialization) {
    MockLoader loader;

    auto font = std::make_shared<Font>("TestResources/Fonts/Vera.ttf", "@!");

    ttvfs::File *fp = Engine::getFileManager()->getOrCreateFile("ASD.ftfont");
    fp->open("wb");

    OutputSerializer s(fp);

    FontUtils::serializeFont(font->getTextureFont(), fp);

    fp->close();
}