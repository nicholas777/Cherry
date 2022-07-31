#include "epch.h"

#include "core/Core.h"
#include "core/Log.h"
#include "OpenGLTexture.h"

#include "stb_image.h"
#include <glad/glad.h>

namespace Cherry
{
	//TODO: Add optional texture parameter customization support
	OpenGLTexture::OpenGLTexture(std::string path)
	{
		int width, height, channels;

		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		CH_ASSERT(data, "failed to load texture image");

		m_Width = width;
		m_Height = height;
		
		GLenum OpenGLFormat;
		if (channels == 3)
		{
			m_Format = GL_RGB;
			OpenGLFormat = GL_RGB8;
		}
		else if (channels == 4)
		{
			m_Format = GL_RGBA;
			OpenGLFormat = GL_RGBA8;
		}

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexImage2D(GL_TEXTURE_2D, 0, m_Format, width, height, 0, m_Format, GL_UNSIGNED_BYTE, data);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		stbi_image_free(data);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void OpenGLTexture::Bind()
	{
	}

	void OpenGLTexture::Bind(int unit)
	{
		glBindTextureUnit(unit, m_TextureID);
	}

}