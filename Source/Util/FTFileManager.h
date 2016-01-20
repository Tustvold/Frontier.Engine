#pragma once
#include <Frontier.h>
#include <vector>

class FTFileManager {
    friend class FTEngine;
public:

    void addSearchPath(const std::string& path);

    std::string getPathToFile(const std::string& path) const;

    std::string getFileContents(const std::string& path) const;

    static bool fileExistsAtPath(const std::string& path);

    static bool directoryExistsAtPath(const std::string& path);

    static void writeToFile(const std::string& path, const std::string& data);

    static void createDirectory(const std::string& path);

    static void deleteEmptyDirectory(const std::string& path);

private:
    FTFileManager();
    ~FTFileManager();

    void setup();

    std::vector<std::string> search_paths_;
    std::string working_directory_;
};
