#pragma once

#include "core/pointer.h"
#include "math/vector.h"

namespace Cherry
{
	enum class FramebufferTextureFormat
	{
		Invalid = 0,

		RGBA8, RedInteger,
		Depth24Stencil8,
	};

	struct FramebufferAttachment
	{
		FramebufferTextureFormat format = FramebufferTextureFormat::Invalid;

		FramebufferAttachment() = default;
		FramebufferAttachment(FramebufferTextureFormat Format)
			: format(Format) {}
	};

	struct FramebufferData
	{
		uint32_t width, height;
		uint32_t samples = 1;

		std::vector<FramebufferAttachment> attachments;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual FramebufferData& GetData() = 0;
		virtual const std::vector<FramebufferAttachment>& GetAttachments() = 0;

		virtual uint32_t GetColorAttachmentID(uint32_t index) = 0;

		virtual int ReadPixel(uint32_t attachmentIndex, uint32_t x, uint32_t y) = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(Vector2f size) = 0;

		static Scoped<Framebuffer> Create(const FramebufferData& data);
	};
}
