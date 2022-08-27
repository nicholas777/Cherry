#include "epch.h"
#include "Platform/OpenGL/OpenGLTexture.h";
#include "Texture.h"
#include "RenderAPI.h"

namespace Cherry
{
	Scoped<Texture> Texture::Create(std::string path)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None: CH_ASSERT(false, "RenderAPI::API::None is not supported") return nullptr;
			case RenderAPI::API::OpenGL: return Scoped<Texture>(new OpenGLTexture(path));
		}
	}

	Scoped<Texture> Texture::Create(uint32_t width, uint32_t height)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None: CH_ASSERT(false, "RenderAPI::API::None is not supported") return nullptr;
		case RenderAPI::API::OpenGL: return Scoped<Texture>(new OpenGLTexture(width, height));
		}
	}
}