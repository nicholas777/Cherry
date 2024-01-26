#pragma once

#include "assetmap.h"

#include <cherry.h>
#include <filesystem>

namespace Cherry {
    class ContentBrowserPanel
    {
    public:
        ContentBrowserPanel(const std::string& directory);
        ~ContentBrowserPanel();

        void SetDirectory(const std::string& directory);
        void ReloadAssets();

        void OnUpdate();

        void WriteAssetmap() { Assetmap::Write(m_AssetmapPath); }

    private:
        std::filesystem::path m_AssetmapPath;
        std::filesystem::path m_ProjectRoot = "";
        std::filesystem::path m_AssetRoot = "";
        std::filesystem::path m_CurrentDir = m_ProjectRoot;

        std::filesystem::path FindAssetmap(std::filesystem::path dir);
    };
} // namespace Cherry
