#include "vertexArray.h"

#include "epch.h"
#include "platform/openGL/openGLVertexArray.h"
#include "renderAPI.h"

namespace Cherry {
    Scoped<VertexArray> VertexArray::Create() {
        switch (RenderAPI::GetAPI()) {
            case RenderAPI::API::None:
                CH_ASSERT(false, "API::None is not supported");
                return nullptr;
            case RenderAPI::API::OpenGL: return Scoped<VertexArray>(new OpenGLVertexArray());
            default: return nullptr;
        }
    }
}
