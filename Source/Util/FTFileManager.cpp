#include "FTFileManager.h"
#include <sys/stat.h>
#include <fstream>

#ifdef WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

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

void FTFileManager::writeToFile(const std::string& file_path, const std::string& data) {
    std::ofstream out(file_path, std::ios::out | std::ios::binary);
    if (out) {
        out.write(&data[0], data.size());
        out.close();
        return;
    }
    FTAssert(false, "IO error whilst writing file");
}

void FTFileManager::createDirectory(const std::string& path) {
#if defined(_WIN32)
    #if defined(_MSC_VER)
        _mkdir(path.c_str());
    #else
        mkdir(path.c_str());
    #endif
#else 
    mkdir(path.c_str(), 0777); // notice that 777 is different than 0777
#endif
}

void FTFileManager::deleteEmptyDirectory(const std::string& path) {
#if defined(_WIN32)
    #if defined(_MSC_VER)
        _rmdir(path.c_str());
    #else
        rmdir(path.c_str());
    #endif
#else 
    rmdir(path.c_str());
#endif
}

bool FTFileManager::fileExistsAtPath(const std::string& path) {
    struct stat buffer;
    if (stat(path.c_str(), &buffer) == -1)
        return false;
    return (buffer.st_mode & S_IFREG) != 0;
}

bool FTFileManager::directoryExistsAtPath(const std::string& path) {
    struct stat buffer;
    if (stat(path.c_str(), &buffer) == -1)
        return false;
    return (buffer.st_mode & S_IFDIR) != 0;
}

