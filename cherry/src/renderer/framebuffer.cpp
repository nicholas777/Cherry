#include "framebuffer.h"

#include "epch.h"
#include "platform/openGL/openGLFramebuffer.h"
#include "renderAPI.h"

namespace Cherry {
    Scoped<Framebuffer> Framebuffer::Create(const FramebufferData& data) {
        switch (RenderAPI::GetAPI()) {
            case RenderAPI::API::None:
                CH_ERROR("API::None is currently not supported");
                return Scoped<Framebuffer>(nullptr);
            case RenderAPI::API::OpenGL: return Scoped<Framebuffer>(new OpenGLFramebuffer(data));
            default: return Scoped<Framebuffer>(nullptr);
        }
    }
}
