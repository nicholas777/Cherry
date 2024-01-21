#include "epch.h"
#include "vertexArray.h"
#include "renderAPI.h"
#include "platform/openGL/openGLVertexArray.h"

namespace Cherry
{
	Scoped<VertexArray> VertexArray::Create()
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None: CH_ASSERT(false, "API::None is not supported"); return nullptr;
			case RenderAPI::API::OpenGL: return Scoped<VertexArray>(new OpenGLVertexArray());
		}
	}
}
