#include "epch.h"
#include "renderingContext.h"
#include "renderAPI.h"
#include "platform/openGL/openGLContext.h"

#include <GLFW/glfw3.h>

namespace Cherry
{
    Scoped<RenderingContext> RenderingContext::Create(void* window)
    {
        switch (RenderAPI::GetAPI())
        {
            case RenderAPI::API::None: CH_ASSERT(false, "API::None is not currently supported");
            case RenderAPI::API::OpenGL: return Scoped<RenderingContext>(new OpenGLContext(static_cast<GLFWwindow*>(window)));
            default: return nullptr;
        }
    }
}
