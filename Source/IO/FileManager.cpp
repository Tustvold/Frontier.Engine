#include "FileManager.h"
#include <ttvfs_zip.h>
#include <boost/filesystem.hpp>
#include <iostream>

using namespace boost::filesystem;

NS_FT_BEGIN

void FileManager::setup() {
    if (!ttvfs::checkCompat()) {
        std::cerr << "ttvfs was compiled with different options than this file!" << std::endl;
    }

    filesystem_root.AddArchiveLoader(new ttvfs::VFSZipArchiveLoader);
    filesystem_root.AddLoader(new ttvfs::DiskLoader);
}

FileManager::FileManager() {
}

FileManager::~FileManager() {
}

void FileManager::addBundle(const std::string &bundle_path, const std::string &rel_path) {
    filesystem_root.AddArchive(bundle_path.c_str());
    filesystem_root.Mount(bundle_path.c_str(), rel_path.c_str());
}

ttvfs::File *FileManager::getFile(const std::string &path) {
    return filesystem_root.GetFile(path.c_str());
}

ttvfs::File *FileManager::getOrCreateFile(const std::string &path) {
    ttvfs::File* ret = getFile(path);
    if (ret)
        return ret;

    //TODO: Add control of mutable paths??
    auto directories = boost::filesystem::path(path).parent_path();
    if (directories.size() != 0)
        create_directories(directories);
    ofstream fs;
    fs.open(path);
    fs.close();
    return getFile(path);
}

NS_FT_END