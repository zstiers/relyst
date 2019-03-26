/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

 // Crap for leak detection
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>

#include <fstream>
#include <vector>
#include <filesystem>

#include <script/script.h>

void MemoryLeakDetection () {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

void GenerateIntermediate (const std::filesystem::path & inputDir, const std::filesystem::path & outputDir) {
    std::vector<char> buffer;
    for (const auto & script : std::filesystem::recursive_directory_iterator(inputDir)) {
        if (!script.is_regular_file())
            continue;

        std::ifstream reader(script, std::ios::ate);
        const auto bytes = std::streamsize(reader.tellg());
        buffer.resize(bytes + 1);
        reader.seekg(0, std::ios::beg);
        reader.read(buffer.data(), bytes);
        const auto gcount = reader.gcount();
        buffer[gcount] = '\0';

        relyst::script::Parse(std::string_view(buffer.data(), gcount));
    }
}

int main (int argc, char * argv[])
{
    MemoryLeakDetection();

    std::filesystem::path testDir = argc > 1 ? argv[1] : TEST_ASSET_DIR;
    GenerateIntermediate(testDir / "in", testDir / "out");
    return 0;
}