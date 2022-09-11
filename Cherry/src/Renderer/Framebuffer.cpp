#include "epch.h"
#include "Framebuffer.h"
#include "RenderAPI.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Cherry
{
	Scoped<Framebuffer> Framebuffer::Create()
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None: CH_ERROR("API::None is currently not supported"); return Scoped<Framebuffer>(nullptr);
			case RenderAPI::API::OpenGL: return Scoped<Framebuffer>(new OpenGLFramebuffer());
		}
	}
}
