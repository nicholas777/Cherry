#pragma once

#include <Cherry.h>
#include <filesystem>
#include "Assetmap.h"

namespace Cherry
{
	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();
		~ContentBrowserPanel();

		void SetDirectory(const std::string& directory);

		void OnUpdate();

	private:
		std::filesystem::path m_AssetmapPath;

		std::filesystem::path FindAssetmap(std::filesystem::path dir);
	};
}