#pragma once

#include "Renderer/Texture.h"
#include <glad/glad.h>

namespace Cherry
{
	class CHERRY_API OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(std::string path);
		OpenGLTexture(uint32_t width, uint32_t height);
		~OpenGLTexture();

		virtual uint32_t GetWidth() override { return m_Width; }
		virtual uint32_t GetHeight() override { return m_Height; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(int unit = 0) override;
	private:
		uint32_t m_Width, m_Height;
		uint32_t m_TextureID;

		GLenum m_Format;
	};
}