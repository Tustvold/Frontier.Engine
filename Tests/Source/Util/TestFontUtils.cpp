#include <gtest/gtest.h>
#include "Rendering/Text/FTFontUtils.h"
#include "Rendering/Text/FTFont.h"
#include "Mock/MockLoader.h"
#include<Util/FTFileManager.h>

TEST(TestFontUtils, FTFontFile) {
    MockLoader mock;
    auto font = std::make_shared<FTFont>("TestResources/Fonts/Vera.ttf");

    ttvfs::File *file = FTEngine::getFileManager()->getOrCreateFile("TestResources/Vera.ftfont");
    file->open("wb");
    FTFontUtils::serializeFont(font->getTextureFont(), file);
    file->close();

    auto font_test = std::make_shared<FTFont>("TestResources/Vera.ftfont");
    font_test.reset();
}

TEST(TestFontUtils, Serialization) {
    MockLoader loader;

    auto font = std::make_shared<FTFont>("TestResources/Fonts/Vera.ttf", "@!");

    ttvfs::File *fp = FTEngine::getFileManager()->getOrCreateFile("ASD.ftfont");
    fp->open("wb");

    OutputSerializer s(fp);

    FTFontUtils::serializeFont(font->getTextureFont(), fp);

    fp->close();
}