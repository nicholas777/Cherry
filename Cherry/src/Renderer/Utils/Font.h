#pragma once

#include "core/Core.h"
#include "core/Log.h"
#include "core/Pointer.h"
#include "Renderer/Texture.h"

#include "freetype-gl.h"

namespace Cherry
{
#if 0
	struct Character
	{
		SubTexture texture;
		Vector2f bearing;
		Vector2f size;
		float advance;

		Character() {}
	};
#endif
	
	class CHERRY_API Font
	{
	public:

		Font(std::string filepath, uint32_t fontSize);

		inline uint32_t GetFontSize() { return m_FontSize; }

		void RenderText(const Vector2f& pos, const std::string& text);
		void RenderText(const Vector2f& pos, const std::string& text, const Vector4f& color, const Vector2f& scale);

	private:
		texture_atlas_t* m_FtTexture;
		texture_font_t* m_FtFont;

		Scoped<Texture> m_Texture;
		std::unordered_map<char, SubTexture> m_SubTextures;

		uint32_t m_FontSize;

	};
}
