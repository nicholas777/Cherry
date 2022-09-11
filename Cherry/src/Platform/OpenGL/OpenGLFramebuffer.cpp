#include "epch.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Cherry
{
	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferData& data)
		: m_Data(data)
	{
		glGenFramebuffers(1, &m_FramebufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);

		TextureParams params;
		params.minFilter = TextureFilter::Linear;
		params.magFilter = TextureFilter::Linear;
		params.wrap = TextureWrap::None;
		params.format = TextureFormat::RGBA;

		m_ColorAttachment = Texture::Create(m_Data.width, m_Data.height, params);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment->GetTextureID(), 0);
		
		TextureParams params2;
		params2.minFilter = TextureFilter::Linear;
		params2.magFilter = TextureFilter::Linear;
		params2.wrap = TextureWrap::None;
		params2.format = TextureFormat::Depth24Stencil8;

		m_DepthStencilAttachment = Texture::Create(m_Data.width, m_Data.height, params2);
		glFramebufferTexture2D(
			GL_FRAMEBUFFER,
			GL_DEPTH_STENCIL_ATTACHMENT,
			GL_TEXTURE_2D, 
			m_DepthStencilAttachment->GetTextureID(), 
			0
		);
		
		CH_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Incomplete framebuffer");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_FramebufferID);
	}

	void OpenGLFramebuffer::Resize(Vector2f size)
	{
		m_Data.width = size.x;
		m_Data.height = size.y;

		if (m_FramebufferID)
		{
			glDeleteFramebuffers(1, &m_FramebufferID);
			m_ColorAttachment.Free();
			m_DepthStencilAttachment.Free();
		}

		glGenFramebuffers(1, &m_FramebufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);

		TextureParams params;
		params.minFilter = TextureFilter::Linear;
		params.magFilter = TextureFilter::Linear;
		params.wrap = TextureWrap::None;
		params.format = TextureFormat::RGBA;

		m_ColorAttachment = Texture::Create(m_Data.width, m_Data.height, params);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment->GetTextureID(), 0);

		TextureParams params2;
		params2.minFilter = TextureFilter::Linear;
		params2.magFilter = TextureFilter::Linear;
		params2.wrap = TextureWrap::None;
		params2.format = TextureFormat::Depth24Stencil8;

		m_DepthStencilAttachment = Texture::Create(m_Data.width, m_Data.height, params2);
		glFramebufferTexture2D(
			GL_FRAMEBUFFER,
			GL_DEPTH_STENCIL_ATTACHMENT,
			GL_TEXTURE_2D,
			m_DepthStencilAttachment->GetTextureID(),
			0
		);

		CH_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Incomplete framebuffer");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}
