#include "ContentBrowserPanel.h"
#include <imgui.h>

namespace Cherry
{


	ContentBrowserPanel::ContentBrowserPanel()
	{
		// TODO: Project system
		SetDirectory("assets/Project");
	}

	ContentBrowserPanel::~ContentBrowserPanel()
	{
		Assetmap::Write(m_AssetmapPath);
	}

	void ContentBrowserPanel::SetDirectory(const std::string& directory)
	{
		m_AssetmapPath = FindAssetmap(directory);

		if (std::filesystem::exists(directory))
		{
			Assetmap::Load(m_AssetmapPath);
		}
		else
		{
			CH_ASSERT(false, "Directory path is invalid");
		}
	}
	
	void ContentBrowserPanel::OnUpdate()
	{
		ImGui::Begin("Content Browser");

		ImGuiTableFlags flags = ImGuiTableFlags_NoBordersInBody | ImGuiTableFlags_RowBg;
		if (ImGui::BeginTable("Assets", 2, flags))
		{
			ImGui::TableSetupColumn("Name");
			ImGui::TableSetupColumn("Type");
			ImGui::TableHeadersRow();

			for (std::pair<const uint32_t, TextureAsset>& asset : AssetManager::GetTextures())
			{
				ImGui::TableNextRow();

				ImGui::TableSetColumnIndex(0);
				ImGui::Text(asset.second.filepath.c_str());

				ImGui::TableSetColumnIndex(1);
				ImGui::Text("Texture");
			}

			ImGui::EndTable();
		}

		ImGui::End();
	}

	// TODO: System for file and directory IO

	std::filesystem::path ContentBrowserPanel::FindAssetmap(std::filesystem::path dir)
	{
		if (!std::filesystem::is_directory(dir))
		{
			CH_ASSERT(false, "Invalid path");
			return std::filesystem::path();
		}

		for (auto& item : std::filesystem::recursive_directory_iterator(dir))
		{
			if (item.path().filename() == "assetmap" && item.path().extension() == ".yaml")
			{
				return item.path();
			}
		}

		return Assetmap::Create(dir);
	}

}
