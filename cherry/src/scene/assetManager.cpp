#include "assetManager.h"

#include "core/log.h"
#include "debug/profiler.h"
#include "epch.h"
#include "sceneSerializer.h"

namespace Cherry {
    // TODO: Proper ID system
    std::unordered_map<uint32_t, TextureAsset> AssetManager::m_Textures;
    std::unordered_map<uint32_t, SceneAsset> AssetManager::m_Scenes;
    std::unordered_map<uint32_t, ScriptAsset> AssetManager::m_Scripts;

    uint32_t AssetManager::CreateTexture(const std::string& filepath, TextureParams params) {
        CH_PROFILE_FUNC();

        TextureAsset texture;
        texture.filepath = filepath;
        texture.ptr = Texture::Create(filepath, params);
        texture.params = params;

        m_Textures.insert(std::make_pair((uint32_t)m_Textures.size(), std::move(texture)));

        return m_Textures.size() - 1;
    }

    uint32_t AssetManager::CreateTexture(uint32_t ID, const std::string& filepath,
                                         TextureParams params) {
        CH_PROFILE_FUNC();

        TextureAsset texture;
        texture.filepath = filepath;
        texture.ptr = Texture::Create(filepath, params);
        texture.params = params;

        m_Textures.insert(std::make_pair(ID, std::move(texture)));

        return ID;
    }

    void AssetManager::CreateTextureIfNotExists(const std::string& filepath, TextureParams params) {
        CH_PROFILE_FUNC();

        for (std::pair<const uint32_t, TextureAsset>& asset: m_Textures) {
            if (asset.second.filepath == filepath)
                return;
        }

        TextureAsset texture;
        texture.filepath = filepath;
        texture.ptr = Texture::Create(filepath, params);
        texture.params = params;

        m_Textures.insert(std::make_pair(m_Textures.size(), std::move(texture)));
    }

    void AssetManager::CreateTextureIfNotExists(uint32_t ID, const std::string& filepath,
                                                TextureParams params) {
        CH_PROFILE_FUNC();

        for (std::pair<const uint32_t, TextureAsset>& asset: m_Textures) {
            if (asset.first == ID)
                return;
        }

        CreateTexture(ID, filepath, params);
    }

    TextureAsset& AssetManager::GetTexture(uint32_t id) {
        CH_PROFILE_FUNC();

        CH_ASSERT(m_Textures.find(id) != m_Textures.end(), "Asset not found");
        return m_Textures[id];
    }

    std::unordered_map<uint32_t, TextureAsset>& AssetManager::GetTextures() {
        return m_Textures;
    }

    uint32_t AssetManager::CreateScene(const std::string& filepath) {
        CH_PROFILE_FUNC();

        SceneAsset asset;
        asset.filepath = filepath;
        asset.ptr = SceneSerializer::Deserialize(filepath);

        m_Scenes.insert(std::make_pair((uint32_t)m_Scenes.size(), std::move(asset)));

        return m_Scenes.size() - 1;
    }

    uint32_t AssetManager::CreateScene(uint32_t ID, const std::string& filepath) {
        CH_PROFILE_FUNC();

        SceneAsset asset;
        asset.filepath = filepath;
        asset.ptr = SceneSerializer::Deserialize(filepath);

        m_Scenes.insert(std::make_pair(ID, std::move(asset)));

        return ID;
    }

    void AssetManager::CreateSceneIfNotExists(const std::string& filepath) {
        CH_PROFILE_FUNC();

        for (std::pair<const uint32_t, SceneAsset>& asset: m_Scenes) {
            if (asset.second.filepath == filepath)
                return;
        }

        SceneAsset asset;
        asset.filepath = filepath;
        asset.ptr = SceneSerializer::Deserialize(filepath);

        m_Scenes.insert(std::make_pair(m_Scenes.size(), std::move(asset)));
    }

    void AssetManager::CreateSceneIfNotExists(uint32_t ID, const std::string& filepath) {
        CH_PROFILE_FUNC();

        for (auto& asset: m_Scenes) {
            if (asset.first == ID)
                return;
        }

        CreateScene(ID, filepath);
    }

    SceneAsset& AssetManager::GetScene(uint32_t id) {
        CH_ASSERT(m_Scenes.find(id) != m_Scenes.end(), "Asset not found");
        return m_Scenes[id];
    }

    std::unordered_map<uint32_t, SceneAsset>& AssetManager::GetScenes() {
        return m_Scenes;
    }

    uint32_t AssetManager::CreateScript(const std::string& filepath) {
        CH_PROFILE_FUNC();

        ScriptAsset asset;
        asset.filepath = filepath;

        m_Scripts.insert(std::make_pair((uint32_t)m_Scripts.size(), std::move(asset)));

        return m_Scripts.size() - 1;
    }

    uint32_t AssetManager::CreateScript(uint32_t id, const std::string& filepath) {
        CH_PROFILE_FUNC();

        ScriptAsset asset;
        asset.filepath = filepath;

        m_Scripts.insert(std::make_pair(id, std::move(asset)));

        return id;
    }

    void AssetManager::CreateScriptIfNotExists(const std::string& filepath) {
        CH_PROFILE_FUNC();

        for (auto& asset: m_Scenes) {
            if (asset.second.filepath == filepath)
                return;
        }

        CreateScript(filepath);
    }

    void AssetManager::CreateScriptIfNotExists(uint32_t id, const std::string& filepath) {
        CH_PROFILE_FUNC();

        for (auto& asset: m_Scenes) {
            if (asset.first == id)
                return;
        }

        CreateScript(id, filepath);
    }

    ScriptAsset& AssetManager::GetScript(uint32_t id) {
        CH_ASSERT(m_Scripts.find(id) != m_Scripts.end(), "Asset not found");
        return m_Scripts[id];
    }

    std::unordered_map<uint32_t, ScriptAsset>& AssetManager::GetScripts() {
        return m_Scripts;
    }

}
