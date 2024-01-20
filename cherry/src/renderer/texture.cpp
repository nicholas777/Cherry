#include "epch.h"
#include "platform/openGL/openGLTexture.h"
#include "texture.h"
#include "renderAPI.h"

namespace Cherry
{
    Shared<Texture> Texture::Create(std::string path)
    {
        switch (RenderAPI::GetAPI())
        {
            case RenderAPI::API::None: CH_ASSERT(false, "RenderAPI::API::None is not supported");
            case RenderAPI::API::OpenGL: return Shared<Texture>(new OpenGLTexture(path));
            default: return nullptr;
        }
    }

    Shared<Texture> Texture::Create(uint32_t width, uint32_t height)
    {
        switch (RenderAPI::GetAPI())
        {
            case RenderAPI::API::None: CH_ASSERT(false, "RenderAPI::API::None is not supported");
            case RenderAPI::API::OpenGL: return Shared<Texture>(new OpenGLTexture(width, height));
            default: return nullptr;
        }
    }

    Shared<Texture> Texture::Create(std::string path, TextureParams params)
    {
        switch (RenderAPI::GetAPI())
        {
            case RenderAPI::API::None: CH_ASSERT(false, "RenderAPI::API::None is not supported");
            case RenderAPI::API::OpenGL: return Shared<Texture>(new OpenGLTexture(path, params));
            default: return nullptr;
        }
    }

    Shared<Texture> Texture::Create(uint32_t width, uint32_t height, TextureParams params)
    {
        switch (RenderAPI::GetAPI())
        {
            case RenderAPI::API::None: CH_ASSERT(false, "RenderAPI::API::None is not supported");
            case RenderAPI::API::OpenGL: return Shared<Texture>(new OpenGLTexture(width, height, params));
            default: return nullptr;
        }
    }

}
