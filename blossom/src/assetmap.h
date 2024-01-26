#pragma once

#include "debug/profiler.h"
#include "scene/assetManager.h"

#include <filesystem>
#include <fstream>
#include <yaml-cpp/yaml.h>

namespace Cherry {
    class Assetmap
    {
    public:
        static void Load(const std::filesystem::path& filepath) {
            CH_PROFILE_FUNC();

            YAML::Node map = YAML::LoadFile(filepath.generic_u8string());

            if (map["Textures"]) {
                for (int i = 0; i < map["Textures"].size(); i++) {
                    YAML::Node texture = map["Textures"][i];

                    AssetManager::CreateTextureIfNotExists(
                        texture["ID"].as<uint32_t>(), texture["File"].as<std::string>(),
                        TextureParams(
                            static_cast<TextureWrap>(texture["Params"]["Wrap"].as<int>()),
                            static_cast<TextureFilter>(texture["Params"]["MinFilter"].as<int>()),
                            static_cast<TextureFilter>(texture["Params"]["MagFilter"].as<int>()),
                            static_cast<TextureFormat>(texture["Params"]["Format"].as<int>())));
                }
            }

            if (map["Scenes"] && map["Scenes"].IsSequence()) {
                for (int i = 0; i < map["Scenes"].size(); i++) {
                    YAML::Node texture = map["Scenes"][i];

                    AssetManager::CreateSceneIfNotExists(texture["ID"].as<uint32_t>(),
                                                         texture["File"].as<std::string>());
                }
            }

            if (map["Scripts"] && map["Scripts"].IsSequence()) {
                for (int i = 0; i < map["Scripts"].size(); i++) {
                    YAML::Node script = map["Scripts"][i];

                    AssetManager::CreateScriptIfNotExists(script["ID"].as<uint32_t>(),
                                                          script["File"].as<std::string>());
                }
            }

            for (auto& entry:
                 std::filesystem::recursive_directory_iterator(filepath.parent_path())) {
                if (entry.path().extension() == ".png") {
                    AssetManager::CreateTextureIfNotExists(entry.path().string());
                    continue;
                }

                if (entry.path().extension() == ".chs") {
                    AssetManager::CreateSceneIfNotExists(entry.path().string());
                    continue;
                }

                if (entry.path().extension() == ".cs") {
                    auto test1 = entry.path().parent_path().filename();

                    AssetManager::CreateScriptIfNotExists(entry.path().string());
                    continue;
                }
            }
        }

        static std::filesystem::path Create(const std::filesystem::path& directory) {
            CH_PROFILE_FUNC();

            std::ofstream stream(directory.generic_u8string() + "/assetmap.yaml",
                                 std::fstream::out);
            stream.close();

            MapDirectory(directory);

            return std::filesystem::path(directory.generic_u8string() + "/assetmap.yaml");
        }

        static void Write(const std::filesystem::path& file) {
            YAML::Emitter out;

            out << YAML::BeginMap; // Root

            out << YAML::Key << "Scenes";
            out << YAML::Value << YAML::BeginSeq; // Scenes

            for (std::pair<const uint32_t, SceneAsset>& asset: AssetManager::GetScenes()) {
                out << YAML::BeginMap; // Asset

                out << YAML::Key << "ID";
                out << YAML::Value << asset.first;

                out << YAML::Key << "File";
                out << YAML::Value << asset.second.filepath;

                out << YAML::EndMap; // Asset
            }

            out << YAML::EndSeq; // Scenes

            out << YAML::Key << "Textures";
            out << YAML::Value << YAML::BeginSeq; // Textures

            for (std::pair<const uint32_t, TextureAsset>& asset: AssetManager::GetTextures()) {
                out << YAML::BeginMap; // Asset

                out << YAML::Key << "ID";
                out << YAML::Value << asset.first;

                out << YAML::Key << "File";
                out << YAML::Value << asset.second.filepath;

                out << YAML::Key << "Params" << YAML::Value << YAML::BeginMap; // Params

                out << YAML::Key << "Format";
                out << YAML::Value << (int)asset.second.params.format;

                out << YAML::Key << "MinFilter";
                out << YAML::Value << (int)asset.second.params.minFilter;

                out << YAML::Key << "MagFilter";
                out << YAML::Value << (int)asset.second.params.magFilter;

                out << YAML::Key << "Wrap";
                out << YAML::Value << (int)asset.second.params.wrap;

                out << YAML::EndMap; // Params
                out << YAML::EndMap; // Asset
            }

            out << YAML::EndSeq; // Textures

            out << YAML::Key << "Scripts";
            out << YAML::Value << YAML::BeginSeq; // Scripts

            for (std::pair<const uint32_t, ScriptAsset>& asset: AssetManager::GetScripts()) {
                out << YAML::BeginMap; // Asset

                out << YAML::Key << "ID";
                out << YAML::Value << asset.first;

                out << YAML::Key << "File";
                out << YAML::Value << asset.second.filepath;

                out << YAML::EndMap; // Asset
            }

            out << YAML::EndSeq; // Scripts

            out << YAML::EndMap; // Root

            std::ofstream stream(file.generic_u8string(), std::fstream::out);
            stream << out.c_str();
            stream.close();
        }

    private:
        static void MapDirectory(const std::filesystem::path& dir) {
            for (auto& entry: std::filesystem::recursive_directory_iterator(dir)) {
                if (entry.path().extension() == ".png") {
                    AssetManager::CreateTexture(entry.path().generic_string());
                    continue;
                }

                if (entry.path().extension() == ".chs") {
                    AssetManager::CreateScene(entry.path().generic_string());
                    continue;
                }

                if (entry.path().extension() == ".cs") {
                    AssetManager::CreateScript(entry.path().generic_string());
                    continue;
                }
            }
        }
    };
} // namespace Cherry
