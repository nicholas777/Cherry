#pragma once

#include "Renderer/Texture.h"
#include "core/Pointer.h"
#include "Scene.h"

namespace Cherry
{
	struct TextureAsset
	{
		Scoped<Texture> ptr;
		std::string filepath;

		TextureParams params;

		TextureAsset() = default;
		TextureAsset(const TextureAsset&) = default;
		TextureAsset(TextureAsset&&) = default;
	};

	struct SceneAsset
	{
		Scoped<Scene> ptr;
		std::string filepath;
	};

	class AssetManager
	{
	public:
		static uint32_t CreateTexture(const std::string& filepath, TextureParams params = TextureParams());
		static uint32_t CreateTexture(uint32_t ID, const std::string& filepath, TextureParams params = TextureParams());
		
		static TextureAsset& GetTexture(uint32_t id);
		static std::unordered_map<uint32_t, TextureAsset>& GetTextures();

		static uint32_t CreateScene(const std::string& filepath);
		static uint32_t CreateScene(uint32_t ID, const std::string& filepath);

		static SceneAsset& GetScene(uint32_t id);
		static std::unordered_map<uint32_t, SceneAsset>& GetScenes();
	private:
		static std::unordered_map<uint32_t, TextureAsset> m_Textures;
		static std::unordered_map<uint32_t, SceneAsset> m_Scenes;
	};
}