#pragma once

#include "Renderer/Texture.h"
#include <glad/glad.h>

namespace Cherry
{
	class CHERRY_API OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(std::string path);
		~OpenGLTexture();

		virtual uint32_t GetWidth() override { return m_Width; }
		virtual uint32_t GetHeight() override { return m_Height; }

		virtual void Bind() override;
		virtual void Bind(int unit) override;
	private:
		uint32_t m_Width, m_Height;
		uint32_t m_TextureID;

		GLenum m_Format;
	};
}