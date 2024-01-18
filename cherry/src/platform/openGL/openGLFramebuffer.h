#pragma once

#include "renderer/framebuffer.h"

namespace Cherry
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferData& data);
		~OpenGLFramebuffer();

		virtual FramebufferData& GetData() override { return m_Data; }
		virtual const std::vector<FramebufferAttachment>& GetAttachments() override { return m_Attachments; }
		virtual uint32_t GetColorAttachmentID(uint32_t index) override { return m_ColorAttachments[index]; }

		virtual int ReadPixel(uint32_t attachmentIndex, uint32_t x, uint32_t y) override;

		virtual void Resize(Vector2f size) override;

		virtual void Bind() override;
		virtual void Unbind() override;
	private:
		uint32_t m_FramebufferID = 0;
		uint32_t* m_AttachmentsGL;

		std::vector<FramebufferAttachment> m_Attachments;
		
		uint32_t m_DepthAttachment;
		FramebufferAttachment m_DepthAttachmentData;

		std::vector<uint32_t> m_ColorAttachments;
		std::vector<FramebufferAttachment> m_ColorAttachmentsData;

		FramebufferData m_Data;

		void RegenerateFramebuffer();
	};
}
