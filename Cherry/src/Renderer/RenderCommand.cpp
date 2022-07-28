#include "epch.h"

#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h";

namespace Cherry
{
	RenderAPI* RenderCommand::s_RenderAPI = new OpenGLRenderAPI();
}