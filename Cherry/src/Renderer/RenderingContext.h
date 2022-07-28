#pragma once

#include "core/Core.h"

namespace Cherry
{
	class CHERRY_API RenderingContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}