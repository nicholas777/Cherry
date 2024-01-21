#include "epch.h"

#include "renderCommand.h"
#include "platform/openGL/openGLRenderAPI.h"

namespace Cherry
{
	RenderAPI* RenderCommand::s_RenderAPI = new OpenGLRenderAPI();
}
