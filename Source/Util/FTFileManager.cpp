#include "FTFileManager.h"
#include <sys/stat.h>
#include <fstream>

void FTFileManager::setup() {

}

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

std::string FTFileManager::getFileContents(const std::string& filename) const {
    auto file_path = getPathToFile(filename);
    FTAssert(file_path != "", "Could not find file with filename %s", filename.c_str());

    //Code taken from http://insanecoding.blogspot.co.uk/2011/11/how-to-read-in-file-in-c.html
    std::ifstream in(file_path, std::ios::in | std::ios::binary);
    if (in) {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    FTAssert(false, "IO error whilst reading file");
}

bool FTFileManager::fileExistsAtPath(const std::string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) != -1);
}