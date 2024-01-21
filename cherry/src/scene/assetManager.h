#pragma once

#include "renderer/texture.h"
#include "core/pointer.h"
#include "scene.h"

namespace Cherry
{
	enum class AssetType
	{
		Unknown = 0,
		Texture, Scene, Script
	};

	struct Asset
	{
		AssetType type;

		Asset(AssetType Type) : type(Type) {}
	};

	struct TextureAsset : public Asset
	{
		Shared<Texture> ptr;
		std::string filepath;

		TextureParams params;

		TextureAsset() : Asset(AssetType::Texture) {}
	};

	struct SceneAsset : public Asset
	{
		Scene* ptr;
		std::string filepath;

		SceneAsset() : Asset(AssetType::Scene), ptr(nullptr) {}
	};

	struct ScriptAsset : public Asset
	{
		std::string filepath;

		ScriptAsset() : Asset(AssetType::Script) {}
	};

	class AssetManager
	{
	public:
		static uint32_t CreateTexture(const std::string& filepath, TextureParams params = TextureParams());
		static uint32_t CreateTexture(uint32_t ID, const std::string& filepath, TextureParams params = TextureParams());
		
		static void CreateTextureIfNotExists(const std::string& filepath, TextureParams params = TextureParams());
		static void CreateTextureIfNotExists(uint32_t ID, const std::string& filepath, TextureParams params = TextureParams());
		
		static TextureAsset& GetTexture(uint32_t id);
		static std::unordered_map<uint32_t, TextureAsset>& GetTextures();

		static uint32_t CreateScene(const std::string& filepath);
		static uint32_t CreateScene(uint32_t ID, const std::string& filepath);

		static void CreateSceneIfNotExists(const std::string& filepath);
		static void CreateSceneIfNotExists(uint32_t ID, const std::string& filepath);

		static SceneAsset& GetScene(uint32_t id);
		static std::unordered_map<uint32_t, SceneAsset>& GetScenes();

		static uint32_t CreateScript(const std::string& filepath);
		static uint32_t CreateScript(uint32_t ID, const std::string& filepath);

		static void CreateScriptIfNotExists(const std::string& filepath);
		static void CreateScriptIfNotExists(uint32_t ID, const std::string& filepath);

		static ScriptAsset& GetScript(uint32_t id);
		static std::unordered_map<uint32_t, ScriptAsset>& GetScripts();
	private:
		static std::unordered_map<uint32_t, TextureAsset> m_Textures;
		static std::unordered_map<uint32_t, SceneAsset> m_Scenes;
		static std::unordered_map<uint32_t, ScriptAsset> m_Scripts;
	};
}
