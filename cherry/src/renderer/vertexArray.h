#pragma once

#include "buffers.h"
#include "core/pointer.h"

namespace Cherry
{
	class VertexArray
	{
	public:

		virtual ~VertexArray() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void AddVertexBuffer(VertexBuffer* buffer) = 0;
		virtual void SetIndexBuffer(IndexBuffer* buffer) = 0;

		virtual std::vector<VertexBuffer*>& GetVertexBuffers() = 0;
		virtual IndexBuffer* GetIndexBuffer() = 0;

		static Scoped<VertexArray> Create();
	};
}
