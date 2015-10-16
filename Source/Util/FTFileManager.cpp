#include "FTFileManager.h"
#include <sys/stat.h>


FTFileManager::FTFileManager() {
}

FTFileManager::~FTFileManager() {
}

void FTFileManager::addSearchPath(const std::string& path) {
    if (path.back() == '/')
        search_paths_.push_back(path);
    else
        search_paths_.push_back(path + "/");
}

std::string FTFileManager::getPathToFile(const std::string& path) const {
    if (fileExistsAtPath(path))
        return path;

    for (auto it = search_paths_.begin(); it != search_paths_.end(); ++it) {
        // NB this is not necessarily an absolute path, it may be a path relative to the working directory
        auto full_path = (*it) + path;
        if (fileExistsAtPath(full_path))
            return full_path;
    }
    return "";
}

bool FTFileManager::fileExistsAtPath(const std::string& path) const {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) != -1);
}

void FTFileManager::setup() {

}
