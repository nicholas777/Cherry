#include "epch.h"
#include "VertexArray.h"
#include "RenderAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

#include <string>

namespace Cherry
{
	VertexArray* VertexArray::Create()
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None: CH_ASSERT(false, "API::None is not supported"); return nullptr;
			case RenderAPI::API::OpenGL: return new OpenGLVertexArray();
		}
	}
}
