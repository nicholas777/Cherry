#pragma once

#include "core/pointer.h"

namespace Cherry
{
	class RenderingContext
	{
	public:

		virtual ~RenderingContext() = default;

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static Scoped<RenderingContext> Create(void* window);
	};
}
