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
	
	void OpenGLVertexArray::AddVertexBuffer(VertexBuffer* buffer)
	{
		glBindVertexArray(m_ID);
		m_VertexBuffers.push_back(buffer);

	}

	void OpenGLVertexArray::SetIndexBuffer(IndexBuffer* buffer)
	{
		glBindVertexArray(m_ID);
		m_IndexBuffer = buffer;
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