#pragma once

#include "renderer/texture.h"

namespace Cherry
{
	class TextureAtlas
	{
	public:
		TextureAtlas() = default;
		TextureAtlas(const std::string& filepath, uint32_t textureWidth, uint32_t textureHeight, uint32_t sheetWidth, uint32_t sheetHeight, uint32_t texturesX, uint32_t texturesY);

		const SubTexture& GetSubTexture(uint32_t x, uint32_t y);

		inline uint32_t GetTextureWidth() { return m_TextureWidth; }
		inline uint32_t GetTextureHeight() { return m_TextureHeight; }

		inline uint32_t GetSheetWidth() { return m_TotalWidth; }
		inline uint32_t GetSheetHeight() { return m_TotalHeight; }
	private:
		Shared<Texture> m_Texture;
		std::vector<SubTexture> m_SubTextures;

		uint32_t m_TextureWidth, m_TextureHeight;
		uint32_t m_TotalWidth, m_TotalHeight;
		uint32_t m_TexturesX, m_TexturesY;
		uint32_t m_TileOffset;
	};
}
