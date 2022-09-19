#pragma once

#include "Renderer/Texture.h"
#include "core/Pointer.h"

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

	class AssetManager
	{
	public:
		uint32_t CreateTexture(const std::string& filepath, TextureParams params = TextureParams());
		TextureAsset& GetTexture(uint32_t id);
	private:
		std::unordered_map<uint32_t, TextureAsset> m_Textures;

		friend class SceneSerializer;
	};
}
