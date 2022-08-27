#pragma once

#include "core/Core.h"
#include "core/Pointer.h"

namespace Cherry
{
	// TODO: Framebuffers
	class CHERRY_API Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() = 0;

		static Scoped<Framebuffer> Create();
	};
}