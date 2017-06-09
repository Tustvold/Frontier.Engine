#pragma once
#include <Frontier.h>
#include <vector>
#include <ttvfs.h>

class FTFileManager {
    friend class FTEngine;
public:

    ttvfs::File* getFile(const std::string& path);

    void addBundle(const std::string& path, const std::string& rel_path);

private:
    FTFileManager();
    ~FTFileManager();

    void setup();

    ttvfs::Root filesystem_root;
};
