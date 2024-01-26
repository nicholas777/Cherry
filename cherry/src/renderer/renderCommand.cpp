#include "renderCommand.h"

#include "epch.h"
#include "platform/openGL/openGLRenderAPI.h"

namespace Cherry {
    RenderAPI* RenderCommand::s_RenderAPI = new OpenGLRenderAPI();
}
