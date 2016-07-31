#include <Mock/MockLoader.h>
#include <FTEngine.h>
#include <Util/FTFileManager.h>
#include <time.h>


TEST(TestFileManager, TestFileExists) {
    MockLoader mock;

    auto file_manager = FTEngine::getFileManager();

    EXPECT_TRUE(file_manager->fileExistsAtPath("TestResources/Textures/checker.DDS"));
    EXPECT_FALSE(file_manager->fileExistsAtPath("TestResources/Textures/non-existent.DDS"));
}

TEST(TestFileManager, TestSearchPaths) {
    MockLoader mock;

    auto file_manager = FTEngine::getFileManager();

    file_manager->addSearchPath("TestResources");

    EXPECT_TRUE(file_manager->fileExistsAtPath("TestResources/Textures/checker.DDS"));
    EXPECT_FALSE(file_manager->fileExistsAtPath("TestResources/Textures/non-existent.DDS"));
    EXPECT_FALSE(file_manager->fileExistsAtPath("TestResources/Textures"));

    EXPECT_EQ(file_manager->getPathToFile("Textures/checker.DDS"), "TestResources/Textures/checker.DDS");
    EXPECT_EQ(file_manager->getPathToFile("Textures/non-existent.DDS"), "");


    file_manager->addSearchPath("TestResources/Textures/");

    EXPECT_EQ(file_manager->getPathToFile("checker.DDS"), "TestResources/Textures/checker.DDS");
    EXPECT_EQ(file_manager->getPathToFile("non-existent.DDS"), "");
}


TEST(TestFileManager, TestReadFile) {
    MockLoader mock;

    auto file_manager = FTEngine::getFileManager();

    file_manager->addSearchPath("TestResources");

    EXPECT_EQ(file_manager->getFileContents("TestReadFile.txt"), "This is a test file.");
}


TEST(TestFileManager, TestWriteFile) {
    MockLoader mock;

    auto file_manager = FTEngine::getFileManager();

    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    auto time_str = asctime(timeinfo);

    file_manager->writeToFile("TestResources/TestWriteOutput.txt", time_str);

    auto read_str = file_manager->getFileContents("TestResources/TestWriteOutput.txt");


    EXPECT_EQ(read_str, time_str);
}

TEST(TestFileManager, TestDirectoryExists) {
    EXPECT_TRUE(FTFileManager::directoryExistsAtPath("TestResources/Textures"));
    EXPECT_FALSE(FTFileManager::directoryExistsAtPath("TestResources/THIS DIRECTORY DOESN'T EXIST"));
    EXPECT_FALSE(FTFileManager::directoryExistsAtPath("TestResources/Textures/checker.DDS"));
}

TEST(TestFileManager, TestCreateDirectory) {
    EXPECT_FALSE(FTFileManager::directoryExistsAtPath("TestResources/TestDir"));
    FTFileManager::createDirectory("TestResources/TestDir");
    EXPECT_TRUE(FTFileManager::directoryExistsAtPath("TestResources/TestDir"));

    FTFileManager::deleteEmptyDirectory("TestResources/TestDir");
    EXPECT_FALSE(FTFileManager::directoryExistsAtPath("TestResources/TestDir"));
}