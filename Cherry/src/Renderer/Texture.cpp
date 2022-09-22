#include "epch.h"
#include "Platform/OpenGL/OpenGLTexture.h";
#include "Texture.h"
#include "RenderAPI.h"

namespace Cherry
{
	Shared<Texture> Texture::Create(std::string path)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None: CH_ASSERT(false, "RenderAPI::API::None is not supported") return nullptr;
			case RenderAPI::API::OpenGL: return Shared<Texture>(new OpenGLTexture(path));
		}
	}

	Shared<Texture> Texture::Create(uint32_t width, uint32_t height)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None: CH_ASSERT(false, "RenderAPI::API::None is not supported") return nullptr;
			case RenderAPI::API::OpenGL: return Shared<Texture>(new OpenGLTexture(width, height));
		}
	}

	Shared<Texture> Texture::Create(std::string path, TextureParams params)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None: CH_ASSERT(false, "RenderAPI::API::None is not supported") return nullptr;
			case RenderAPI::API::OpenGL: return Shared<Texture>(new OpenGLTexture(path, params));
		}
	}

	Shared<Texture> Texture::Create(uint32_t width, uint32_t height, TextureParams params)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None: CH_ASSERT(false, "RenderAPI::API::None is not supported") return nullptr;
		case RenderAPI::API::OpenGL: return Shared<Texture>(new OpenGLTexture(width, height, params));
		}
	}

}
