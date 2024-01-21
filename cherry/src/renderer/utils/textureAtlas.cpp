#include "epch.h"

#include "textureAtlas.h"
#include "debug/profiler.h"

namespace Cherry
{
	// TODO: Support for space in between tiles
	TextureAtlas::TextureAtlas(const std::string& filepath, uint32_t textureWidth, uint32_t textureHeight, uint32_t sheetWidth, uint32_t sheetHeight, uint32_t texturesX, uint32_t texturesY)
	{
		CH_PROFILE_FUNC();

		m_TextureWidth = textureWidth;
		m_TextureHeight = textureHeight;

		m_TotalWidth = sheetWidth;
		m_TotalHeight = sheetHeight;

		m_TexturesX = texturesX;
		m_TexturesY = texturesY;

		m_Texture = Texture::Create(filepath);

		m_SubTextures = std::vector<SubTexture>();
		m_SubTextures.reserve(texturesX * texturesY);
		
		for (int y = 0; y < texturesY; y++)
		{
			for (int x = 0; x < texturesX; x++)
			{
				float minX = x * m_TextureWidth;
				float minY = y * m_TextureHeight;

				float maxX = (x + 1) * m_TextureWidth;
				float maxY = (y + 1) * m_TextureHeight;

				SubTexture tex(
					m_Texture.Get(),
					Vector2f(minX / m_TotalWidth, 1 - (minY / m_TotalHeight)),
					Vector2f(maxX / m_TotalWidth, 1 - (minY / m_TotalHeight)),
					Vector2f(maxX / m_TotalWidth, 1 - (maxY / m_TotalHeight)),
					Vector2f(minX / m_TotalWidth, 1 - (maxY / m_TotalHeight))
				);
				m_SubTextures.push_back(tex);
			}
		}
	}

	const SubTexture& TextureAtlas::GetSubTexture(uint32_t x, uint32_t y)
	{
		return m_SubTextures[y * m_TexturesX + x];
	}
}
