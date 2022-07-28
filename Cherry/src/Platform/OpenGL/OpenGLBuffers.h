#pragma once

#include "Renderer/Buffers.h"

#include <cstdint>

namespace Cherry
{
	class CHERRY_API OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* data, uint32_t size, BufferLayout layout);
		~OpenGLVertexBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual BufferLayout& GetLayout() override;
		virtual void SetLayout(BufferLayout newLayout) override;

	private:
		uint32_t m_BufferID;
		BufferLayout m_Layout;

		void GenVertexAttribPointers();
	};

	class CHERRY_API OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* data, uint32_t size);
		~OpenGLIndexBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;
		virtual uint32_t GetCount() override;
	private:
		uint32_t m_ID;
		uint32_t m_Count;
	};
}