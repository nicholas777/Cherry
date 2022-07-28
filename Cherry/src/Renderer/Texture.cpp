#include "epch.h"
#include "Platform/OpenGL/OpenGLTexture.h";
#include "Texture.h"
#include "RenderAPI.h"

namespace Cherry
{
	Texture* Texture::Create(std::string path)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None: CH_ASSERT(false, "RenderAPI::API::None is not supported") return nullptr;
			case RenderAPI::API::OpenGL: return new OpenGLTexture(path);
		}
	}
}