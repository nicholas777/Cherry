#include "epch.h"
#include "shader.h"
#include "platform/openGL/openGLShader.h"
#include "renderAPI.h"

namespace Cherry
{
    Scoped<Shader> Shader::Create(std::string vertexSrc, std::string fragmentSrc)
    {
        switch (RenderAPI::GetAPI())
        {
            case RenderAPI::API::None: CH_ASSERT(false, "API::None is not supported");
            case RenderAPI::API::OpenGL: return Scoped<Shader>(new OpenGLShader(vertexSrc, fragmentSrc));
            default: return nullptr;
        }
    }

    Scoped<Shader> Shader::Create(std::string file)
    {
        switch (RenderAPI::GetAPI())
        {
            case RenderAPI::API::None: CH_ASSERT(false, "API::None is not supported");
            case RenderAPI::API::OpenGL: return Scoped<Shader>(new OpenGLShader(file));
            default: return nullptr;
        }
    }

}
