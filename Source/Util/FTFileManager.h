#pragma once
#include <Frontier.h>
#include <vector>

class FTFileManager {
    friend class FTEngine;
public:

    void addSearchPath(const std::string& path);

    std::string getPathToFile(const std::string& path) const;

    bool fileExistsAtPath(const std::string& path) const;

private:
    FTFileManager();
    ~FTFileManager();

    void setup();

    std::vector<std::string> search_paths_;
    std::string working_directory_;
};
