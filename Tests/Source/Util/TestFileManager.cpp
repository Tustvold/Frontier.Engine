#include <Mock/MockLoader.h>
#include <FTEngine.h>
#include <Util/FTFileManager.h>


TEST(TestFileManager, TestFileExists) {
    MockLoader mock;

    auto file_manager = FTEngine::getFileManager();

    EXPECT_TRUE(file_manager->fileExistsAtPath("Resources/Textures/checker.DDS"));
    EXPECT_FALSE(file_manager->fileExistsAtPath("Resources/Textures/non-existent.DDS"));
}

TEST(TestFileManager, TestSearchPaths) {
    MockLoader mock;

    auto file_manager = FTEngine::getFileManager();

    file_manager->addSearchPath("Resources");

    EXPECT_TRUE(file_manager->fileExistsAtPath("Resources/Textures/checker.DDS"));
    EXPECT_FALSE(file_manager->fileExistsAtPath("Resources/Textures/non-existent.DDS"));

    EXPECT_EQ(file_manager->getPathToFile("Textures/checker.DDS"), "Resources/Textures/checker.DDS");
    EXPECT_EQ(file_manager->getPathToFile("Textures/non-existent.DDS"), "");


    file_manager->addSearchPath("Resources/Textures/");

    EXPECT_EQ(file_manager->getPathToFile("checker.DDS"), "Resources/Textures/checker.DDS");
    EXPECT_EQ(file_manager->getPathToFile("non-existent.DDS"), "");
}


TEST(TestFileManager, TestReadFile) {
    MockLoader mock;

    auto file_manager = FTEngine::getFileManager();

    file_manager->addSearchPath("Resources");

    EXPECT_EQ(file_manager->getFileContents("TestReadFile.txt"), "This is a test file.");
}