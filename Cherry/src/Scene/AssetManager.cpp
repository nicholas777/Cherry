#include "epch.h"
#include "AssetManager.h"

#include "core/Core.h"
#include "core/Log.h"

namespace Cherry
{

	uint32_t AssetManager::CreateTexture(const std::string& filepath, TextureParams params)
	{
		
		TextureAsset texture;
		texture.filepath = filepath;
		texture.ptr = Texture::Create(filepath, params);
		texture.params = params;

		m_Textures.insert(std::make_pair((uint32_t)m_Textures.size(), std::move(texture)));

		return m_Textures.size() - 1;
	}

	TextureAsset& AssetManager::GetTexture(uint32_t id)
	{
		CH_ASSERT(m_Textures.find(id) != m_Textures.end(), "Asset not found");
		return m_Textures[id];
	}
}
