#pragma once

#include "Renderer/Texture.h"
#include <glad/glad.h>

namespace Cherry
{
	class OpenGLTexture : public Texture
	{
	public:
		// TODO: Merge constructors into two
		OpenGLTexture(std::string path);
		OpenGLTexture(uint32_t width, uint32_t height);

		OpenGLTexture(std::string path, TextureParams params);
		OpenGLTexture(uint32_t width, uint32_t height, TextureParams params);

		~OpenGLTexture();

		virtual uint32_t GetWidth() override { return m_Width; }
		virtual uint32_t GetHeight() override { return m_Height; }

		virtual uint32_t GetTextureID() override { return m_TextureID; };

		virtual void ResetParams(TextureParams params) override;
		virtual void SetData(void* data) override;

		virtual void Bind(int unit = 0) override;
	private:
		uint32_t m_Width, m_Height;
		uint32_t m_TextureID;

		GLenum m_Format, m_InternalFormat;
	};
}