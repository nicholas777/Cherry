#pragma once

#include "core/Core.h"
#include "core/Pointer.h"
#include "Math/Vector.h"

namespace Cherry
{
	struct FramebufferData
	{
		uint32_t width, height;

		uint32_t samples = 1;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual FramebufferData& GetData() = 0;

		virtual uint32_t GetColorAttachment() = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(Vector2f size) = 0;

		static Scoped<Framebuffer> Create(const FramebufferData& data);
	};
}