#pragma once

#include "Renderer/Framebuffer.h"
#include "Renderer/Texture.h"

namespace Cherry
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferData& data);
		~OpenGLFramebuffer();

		virtual FramebufferData& GetData() override { return m_Data; }

		virtual uint32_t GetColorAttachment() override { return m_ColorAttachment->GetTextureID(); }

		virtual void Resize(Vector2f size) override;

		virtual void Bind() override;
		virtual void Unbind() override;
	private:
		uint32_t m_FramebufferID;
		Scoped<Texture> m_ColorAttachment, m_DepthStencilAttachment;
		FramebufferData m_Data;
	};
}