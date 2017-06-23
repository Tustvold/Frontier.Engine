#include <iostream>
#include <unordered_map>
#include "ttvfs.h"
#include "miniz.h"
#include <regex>

#include <boost/filesystem.hpp>
#include <Rendering/Text/FTFont.h>
#include <Rendering/Text/FTFontUtils.h>
#include <Util/FTFileManager.h>

USING_NS_FT
using namespace boost::filesystem;

typedef bool (*ProcessFileCallback)(const path &filename, const path &tmpDir, const path &input_dir);

bool fileIsUpToDate(const path &input, const path &output) {
    if (!exists(input) || !exists(output))
        return false;

    auto t1 = last_write_time(input);
    auto t2 = last_write_time(output);

    return t2 > t1;
}

bool identityProcessor(const path &input, const path &tmpDir, const path &input_dir) {
    const path output = tmpDir / input.lexically_relative(input_dir.parent_path());

    if (fileIsUpToDate(input, output))
        return false;

    create_directories(output.parent_path());
    copy_file(input, output, detail::overwrite_if_exists);
    return true;
}


bool ttfProcessor(const path &input, const path &tmpDir, const path &input_dir) {
    path copy = input.lexically_relative(input_dir.parent_path());
    const path output = tmpDir / copy.replace_extension("ftfont");

    if (fileIsUpToDate(input, output))
        return false;

    create_directories(output.parent_path());

    auto font = std::make_shared<FTFont>(input.string());

    ttvfs::File *fp = FTEngine::getFileManager()->getOrCreateFile(output.string());
    fp->open("wb");

    FTFontUtils::serializeFont(font->getTextureFont(), fp);

    fp->close();

    return true;
}


std::vector<std::pair<std::regex, ProcessFileCallback>> extension_handlers = {
        {std::regex(".ttf"), ttfProcessor},
        {std::regex(".*"),   identityProcessor},
};

static void print_help() {
    printf("Expected <Input Directory> <Temporary Directory> <Output File>\n");
}

static bool generate_temporary_files(const path &input_name, const path &temporary_dir_name) {

    bool modified = false;

    recursive_directory_iterator iter(input_name);
    recursive_directory_iterator end_iter;
    for (; iter != end_iter; ++iter) {


        auto full_path = iter->path();

        if (is_directory(full_path))
            continue;

        auto extension = full_path.extension().string();


        printf("Processing File %s \n", (*iter).path().c_str());

        for (auto &handler : extension_handlers) {
            if (std::regex_match(extension, handler.first)) {
                modified |= handler.second(full_path, temporary_dir_name, input_name);
                break;
            }
        }

    }
    return modified;
}

static void compress(const path &input_name, const path &temporary_dir_name, const path &output_file_name) {

    const path &root_path = temporary_dir_name / input_name.filename();

    recursive_directory_iterator iter(root_path);
    recursive_directory_iterator end_iter;


    mz_zip_archive zip;
    memset(&zip, 0, sizeof(zip));

    if (MZ_FALSE == mz_zip_writer_init_file(&zip, output_file_name.c_str(), 128 * 1024)) {
        std::cerr << "mz_zip_writer_init_file failed" << std::endl;
        return;
    }

    for (; iter != end_iter; ++iter) {
        auto &externalPath = iter->path();

        if (is_directory(externalPath))
            continue;

        const path internalPath = externalPath.lexically_relative(root_path);

        printf("Compressing File %s \n", externalPath.c_str());

        if (MZ_FALSE == mz_zip_writer_add_file(&zip, internalPath.c_str(),
                                               externalPath.c_str(), NULL, 0, MZ_DEFAULT_COMPRESSION)) {
            std::cerr << "mz_zip_writer_add_file failed on file "
                      << internalPath << std::endl;

            return;
        }
    }

    if (MZ_FALSE == mz_zip_writer_finalize_archive(&zip)) {
        std::cerr << "mz_zip_writer_finalize_archive failed" << std::endl;
        return;
    }

    if (MZ_FALSE == mz_zip_writer_end(&zip)) {
        std::cerr << "mz_zip_writer_end failed" << std::endl;
        return;
    }
}

int main(int argc, const char *argv[]) {
    FTEngine::setup(true, false);

    if (argc != 4) {
        print_help();
        return 1;
    }

    const path input_name = argv[1];
    const path temporary_dir_name = argv[2];
    const path output_file_name = argv[3];

    bool modified = generate_temporary_files(input_name, temporary_dir_name);

    if (!exists(output_file_name) || modified)
        compress(input_name, temporary_dir_name, output_file_name);

    FTEngine::cleanup();

    return 0;
}