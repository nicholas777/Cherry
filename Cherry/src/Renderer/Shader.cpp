#include "epch.h"
#include "Shader.h"
#include "RenderAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <string>

namespace Cherry
{
	Scoped<Shader> Shader::Create(std::string vertexSrc, std::string fragmentSrc)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None: CH_ASSERT(false, "API::None is not supported"); return nullptr;
			case RenderAPI::API::OpenGL: return Scoped<Shader>(new OpenGLShader(vertexSrc, fragmentSrc));
		}
	}

	Scoped<Shader> Shader::Create(std::string file)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None: CH_ASSERT(false, "API::None is not supported"); return nullptr;
			case RenderAPI::API::OpenGL: return Scoped<Shader>(new OpenGLShader(file));
		}
	}

}