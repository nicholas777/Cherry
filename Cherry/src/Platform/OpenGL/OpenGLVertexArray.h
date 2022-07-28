#pragma once

#include "Renderer/vertexArray.h"
#include "Renderer/Buffers.h"

#include <vector>
#include <cstdint>

namespace Cherry
{
	class CHERRY_API OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void AddVertexBuffer(float* data, uint32_t size, BufferLayout layout) override;
		virtual void SetIndexBuffer(uint32_t* data, uint32_t size) override;

		virtual std::vector<VertexBuffer*>& GetVertexBuffers() override;
		virtual IndexBuffer* GetIndexBuffer() override;
	private:
		uint32_t m_ID;
		std::vector<VertexBuffer*> m_VertexBuffers;
		IndexBuffer* m_IndexBuffer;
	};
}