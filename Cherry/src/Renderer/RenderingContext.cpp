#include "epch.h"
#include "RenderingContext.h"
#include "RenderAPI.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>

namespace Cherry
{
	Scoped<RenderingContext> RenderingContext::Create(void* window)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None:
			CH_ASSERT(false, "API::None is not currently supported");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return Scoped<RenderingContext>(new OpenGLContext(static_cast<GLFWwindow*>(window)));
		}
	}
}
