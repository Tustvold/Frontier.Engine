#include "FTFileManager.h"
#include <ttvfs_zip.h>
#include <boost/filesystem.hpp>
#include <iostream>

using namespace boost::filesystem;

void FTFileManager::setup() {
    if (!ttvfs::checkCompat()) {
        std::cerr << "ttvfs was compiled with different options than this file!" << std::endl;
    }

    filesystem_root.AddLoader(new ttvfs::DiskLoader);
    filesystem_root.AddArchiveLoader(new ttvfs::VFSZipArchiveLoader);
}

FTFileManager::FTFileManager() {
}

FTFileManager::~FTFileManager() {
}

void FTFileManager::addBundle(const std::string &bundle_path, const std::string &rel_path) {
    filesystem_root.AddArchive(bundle_path.c_str());
    filesystem_root.Mount(bundle_path.c_str(), rel_path.c_str());
}

ttvfs::File *FTFileManager::getFile(const std::string &path) {
    return filesystem_root.GetFile(path.c_str());
}

