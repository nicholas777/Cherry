#pragma once

#include "Buffers.h"
#include "core/Pointer.h"

#include <vector>

namespace Cherry
{
	class CHERRY_API VertexArray
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