#include "epch.h"
#include "Buffers.h"
#include "RenderAPI.h"

#include "Platform/OpenGL/OpenGLBuffers.h"

#include <cstdint>

namespace Cherry
{
	VertexBuffer* VertexBuffer::Create(float* data, uint32_t size, BufferLayout layout)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None: CH_ASSERT(false, "RenderAPI::API::None is not supported"); return nullptr;
			case RenderAPI::API::OpenGL: return new OpenGLVertexBuffer(data, size, layout);
		}
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* data, uint32_t size)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None: CH_ASSERT(false, "RenderAPI::API::None is not supported"); return nullptr;
			case RenderAPI::API::OpenGL: return new OpenGLIndexBuffer(data, size);
		}
	}

}