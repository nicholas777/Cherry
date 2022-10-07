#include "epch.h"
#include "Buffers.h"
#include "RenderAPI.h"

#include "Platform/OpenGL/OpenGLBuffers.h"

#include <cstdint>

namespace Cherry
{
	Scoped<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None: CH_ASSERT(false, "RenderAPI::API::None is not supported"); return nullptr;
			case RenderAPI::API::OpenGL: return Scoped<VertexBuffer>(new OpenGLVertexBuffer(size));
		}
	}

	Scoped<VertexBuffer> VertexBuffer::Create(float* data, uint32_t size)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None: CH_ASSERT(false, "RenderAPI::API::None is not supported"); return nullptr;
			case RenderAPI::API::OpenGL: return Scoped<VertexBuffer>(new OpenGLVertexBuffer(data, size));
		}
	}

	Scoped<VertexBuffer> VertexBuffer::Create(float* data, uint32_t size, BufferLayout layout)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None: CH_ASSERT(false, "RenderAPI::API::None is not supported"); return nullptr;
			case RenderAPI::API::OpenGL: return Scoped<VertexBuffer>(new OpenGLVertexBuffer(data, size, layout));
		}
	}

	Scoped<IndexBuffer> IndexBuffer::Create(uint32_t* data, uint32_t size)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None: CH_ASSERT(false, "RenderAPI::API::None is not supported"); return Scoped<IndexBuffer>(nullptr);
			case RenderAPI::API::OpenGL: return Scoped<IndexBuffer>(new OpenGLIndexBuffer(data, size));
		}
	}

}
