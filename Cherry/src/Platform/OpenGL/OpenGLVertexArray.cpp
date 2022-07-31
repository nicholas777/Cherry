#include "epch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Cherry
{
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_ID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_ID);
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_ID);
	}

	void OpenGLVertexArray::Unbind()
	{
		glBindVertexArray(0);
	}
	
	void OpenGLVertexArray::AddVertexBuffer(float* data, uint32_t size, BufferLayout layout)
	{
		glBindVertexArray(m_ID);
		m_VertexBuffers.push_back(VertexBuffer::Create(data, size, layout));

	}

	void OpenGLVertexArray::SetIndexBuffer(uint32_t* data, uint32_t size)
	{
		glBindVertexArray(m_ID);
		m_IndexBuffer = IndexBuffer::Create(data, size);
	}

	std::vector<VertexBuffer*>& OpenGLVertexArray::GetVertexBuffers()
	{
		return m_VertexBuffers;
	}

	IndexBuffer* OpenGLVertexArray::GetIndexBuffer()
	{
		return m_IndexBuffer;
	}
}