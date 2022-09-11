#pragma once

#include "Renderer/vertexArray.h"
#include "Renderer/Buffers.h"

#include <vector>
#include <cstdint>

namespace Cherry
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void AddVertexBuffer(VertexBuffer* buffer) override;
		virtual void SetIndexBuffer(IndexBuffer* buffer) override;

		virtual std::vector<VertexBuffer*>& GetVertexBuffers() override;
		virtual IndexBuffer* GetIndexBuffer() override;
	private:
		uint32_t m_ID;
		std::vector<VertexBuffer*> m_VertexBuffers;
		IndexBuffer* m_IndexBuffer;
	};
}