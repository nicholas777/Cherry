#pragma once

#include <filesystem>

namespace Cherry {
    class Assetmap
    {
    public:
        static void Load(const std::filesystem::path& filepath);
        static void Write(const std::filesystem::path& file);
        static std::filesystem::path Create(const std::filesystem::path& directory);

    private:
        static void MapDirectory(const std::filesystem::path& dir);
    };
} // namespace Cherry
