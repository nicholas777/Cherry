#include "contentBrowserPanel.h"

#include "editorLayer.h"

#include <imgui.h>
#include <system/fileDialogs.h>

namespace Cherry {

    ContentBrowserPanel::ContentBrowserPanel(const std::string& directory) {
        // TODO: Project system
        SetDirectory(directory);
    }

    ContentBrowserPanel::~ContentBrowserPanel() {
        Assetmap::Write(m_AssetmapPath);
    }

    void ContentBrowserPanel::SetDirectory(const std::string& directory) {
        CH_PROFILE_FUNC();

        m_AssetmapPath = FindAssetmap(directory);

        if (std::filesystem::exists(directory) && std::filesystem::is_directory(directory)) {
            m_ProjectRoot = std::filesystem::path(directory);
            m_AssetRoot = m_ProjectRoot;
            m_CurrentDir = m_AssetRoot;
            Assetmap::Load(m_ProjectRoot);
        } else {
            CH_ASSERT(false, "Directory path is invalid");
        }
    }

    void ContentBrowserPanel::ReloadAssets() {
        CH_PROFILE_FUNC();

        m_AssetmapPath = FindAssetmap(m_ProjectRoot);
        Assetmap::Load(m_AssetmapPath);
    }

    void ContentBrowserPanel::OnUpdate() {
        CH_PROFILE_FUNC();

        ImGui::Begin("Content Browser");

        ImGuiTableFlags flags = ImGuiTableFlags_NoBordersInBody | ImGuiTableFlags_RowBg;
        if (ImGui::BeginTable("Assets", 2, flags)) {
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Type");
            ImGui::TableHeadersRow();

            if (m_CurrentDir != m_AssetRoot) {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);

                if (ImGui::Selectable("../", false, ImGuiSelectableFlags_SpanAllColumns)) {
                    m_CurrentDir = m_CurrentDir.parent_path();
                }

                ImGui::TableSetColumnIndex(1);
                ImGui::Text("Directory");
            }

            for (auto& entry: std::filesystem::directory_iterator(m_CurrentDir)) {
                if (entry.is_directory()) {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);

                    if (ImGui::Selectable(entry.path().filename().string().c_str(), false,
                                          ImGuiSelectableFlags_SpanAllColumns)) {
                        m_CurrentDir = entry.path();
                    }

                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("Directory");
                }
            }

            for (std::pair<const uint32_t, TextureAsset>& asset: AssetManager::GetTextures()) {
                if (std::filesystem::path(asset.second.filepath).parent_path() == m_CurrentDir) {
                    ImGui::TableNextRow();

                    ImGui::TableSetColumnIndex(0);
                    if (ImGui::Selectable(std::filesystem::path(asset.second.filepath)
                                              .filename()
                                              .string()
                                              .c_str(),
                                          false, ImGuiSelectableFlags_SpanAllColumns)) {
                        EditorLayer::SelectAsset(&asset.second);
                    }

                    if (ImGui::BeginDragDropSource()) {
                        ImGui::SetDragDropPayload("AssetTexture", &asset.first, sizeof(uint32_t));
                        ImGui::Text(asset.second.filepath.c_str());
                        ImGui::EndDragDropSource();
                    }

                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("Texture");
                }
            }

            for (std::pair<const uint32_t, SceneAsset>& asset: AssetManager::GetScenes()) {
                if (std::filesystem::path(asset.second.filepath).parent_path() == m_CurrentDir) {
                    ImGui::TableNextRow();

                    ImGui::TableSetColumnIndex(0);
                    if (ImGui::Selectable(std::filesystem::path(asset.second.filepath)
                                              .filename()
                                              .string()
                                              .c_str(),
                                          false, ImGuiSelectableFlags_SpanAllColumns)) {
                        EditorLayer::SelectAsset(&asset.second);
                    }

                    if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
                        EditorLayer::SelectScene(asset.second.ptr, asset.second.filepath);
                    }

                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("Scene");
                }
            }

            for (std::pair<const uint32_t, ScriptAsset>& asset: AssetManager::GetScripts()) {
                if (std::filesystem::path(asset.second.filepath).parent_path() == m_CurrentDir) {
                    ImGui::TableNextRow();

                    ImGui::TableSetColumnIndex(0);
                    if (ImGui::Selectable(std::filesystem::path(asset.second.filepath)
                                              .filename()
                                              .string()
                                              .c_str(),
                                          false, ImGuiSelectableFlags_SpanAllColumns)) {
                        EditorLayer::SelectAsset(&asset.second);
                    }

                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("Scene");
                }
            }

            ImGui::EndTable();
        }

        if (ImGui::BeginPopupContextWindow()) {
            if (ImGui::BeginMenu("New")) {
                if (ImGui::MenuItem("Scene")) {
                    std::string path =
                        FileDialogManager::SaveFile("Cherry Scene (.chs)\0*.chs\0\0");
                    Scene* scene = new Scene;
                    SceneSerializer::Serialize(scene, path);
                }

                ImGui::EndMenu();
            }

            ImGui::EndPopup();
        }

        ImGui::End();
    }

    // TODO: System for file and directory IO

    std::filesystem::path ContentBrowserPanel::FindAssetmap(std::filesystem::path dir) {
        CH_PROFILE_FUNC();

        if (!std::filesystem::is_directory(dir)) {
            CH_ASSERT(false, "Invalid path");
            return std::filesystem::path();
        }

        for (auto& item: std::filesystem::recursive_directory_iterator(dir)) {
            if (item.path().filename() == "assetmap.yaml") {
                return item.path();
            }
        }

        return Assetmap::Create(dir);
    }

} // namespace Cherry
