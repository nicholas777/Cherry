#include "epch.h"
#include "Shader.h"
#include "RenderAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <string>

namespace Cherry
{
	Shader* Shader::Create(std::string vertexSrc, std::string fragmentSrc)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None: CH_ASSERT(false, "API::None is not supported"); return nullptr;
			case RenderAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}
	}

	Shader* Shader::Create(std::string file)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None: CH_ASSERT(false, "API::None is not supported"); return nullptr;
			case RenderAPI::API::OpenGL: return new OpenGLShader(file);
		}
	}

}