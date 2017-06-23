#pragma once
#include <Frontier.h>
#include <vector>
#include <ttvfs.h>

NS_FT_BEGIN

class FTFileManager {
    friend class FTEngine;
public:

    ttvfs::File* getFile(const std::string& path);

    ttvfs::File* getOrCreateFile(const std::string& path);

    void addBundle(const std::string& path, const std::string& rel_path);

private:
    FTFileManager();
    ~FTFileManager();

    void setup();

    ttvfs::Root filesystem_root;
};

NS_FT_END