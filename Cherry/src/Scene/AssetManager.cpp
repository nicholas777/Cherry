#include "epch.h"
#include "AssetManager.h"

#include "core/Core.h"
#include "core/Log.h"
#include "SceneSerializer.h"

namespace Cherry
{
	// TODO: Proper ID system
	std::unordered_map<uint32_t, TextureAsset> AssetManager::m_Textures;
	std::unordered_map<uint32_t, SceneAsset> AssetManager::m_Scenes;

	uint32_t AssetManager::CreateTexture(const std::string& filepath, TextureParams params)
	{
		TextureAsset texture;
		texture.filepath = filepath;
		texture.ptr = Texture::Create(filepath, params);
		texture.params = params;

		m_Textures.insert(std::make_pair((uint32_t)m_Textures.size(), std::move(texture)));

		return m_Textures.size() - 1;
	}

	uint32_t AssetManager::CreateTexture(uint32_t ID, const std::string& filepath, TextureParams params)
	{
		TextureAsset texture;
		texture.filepath = filepath;
		texture.ptr = Texture::Create(filepath, params);
		texture.params = params;

		m_Textures.insert(std::make_pair(ID, std::move(texture)));

		return ID;
	}

	TextureAsset& AssetManager::GetTexture(uint32_t id)
	{
		CH_ASSERT(m_Textures.find(id) != m_Textures.end(), "Asset not found");
		return m_Textures[id];
	}

	std::unordered_map<uint32_t, TextureAsset>& AssetManager::GetTextures()
	{
		return m_Textures;
	}

	uint32_t AssetManager::CreateScene(const std::string& filepath)
	{
		SceneAsset asset;
		asset.filepath = filepath;
		asset.ptr = SceneSerializer::Deserialize(filepath);

		m_Scenes.insert(std::make_pair((uint32_t)m_Scenes.size(), std::move(asset)));

		return m_Scenes.size() - 1;
	}

	uint32_t AssetManager::CreateScene(uint32_t ID, const std::string& filepath)
	{
		SceneAsset asset;
		asset.filepath = filepath;
		asset.ptr = SceneSerializer::Deserialize(filepath);

		m_Scenes.insert(std::make_pair(ID, std::move(asset)));

		return ID;
	}

	SceneAsset& AssetManager::GetScene(uint32_t id)
	{
		CH_ASSERT(m_Scenes.find(id) != m_Scenes.end(), "Asset not found");
		return m_Scenes[id];
	}

	std::unordered_map<uint32_t, SceneAsset>& AssetManager::GetScenes()
	{
		return m_Scenes;
	}

}
