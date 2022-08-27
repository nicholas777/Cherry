#include "epch.h"
#include "Framebuffer.h"

namespace Cherry
{
	Scoped<Framebuffer> Framebuffer::Create()
	{
		return Scoped<Framebuffer>(nullptr);
	}
}
