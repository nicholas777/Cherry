#pragma once

#include "core/Core.h"
#include "core/Pointer.h"

namespace Cherry
{
	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() = 0;

		static Scoped<Framebuffer> Create();
	};
}