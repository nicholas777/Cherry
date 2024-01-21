#include "epch.h"

#include "openGLBuffers.h"
#include "debug/profiler.h"

#include <glad/glad.h>

namespace Cherry
{
	static uint32_t ShaderDataTypeToGLType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Boolean:	return GL_BOOL;
		case ShaderDataType::Float:		return GL_FLOAT;
		case ShaderDataType::Float2:	return GL_FLOAT;
		case ShaderDataType::Float3:	return GL_FLOAT;
		case ShaderDataType::Float4:	return GL_FLOAT;
		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::Int2:		return GL_INT;
		case ShaderDataType::Int3:		return GL_INT;
		case ShaderDataType::Int4:		return GL_INT;
		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;
		}
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

		m_Size = size;

		m_Inserts = 0;
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, uint32_t size)
	{
		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);

		m_Size = size;

		m_Inserts = 0;
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, uint32_t size, BufferLayout layout)
	{
		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);

		m_Size = size * 4;

		m_Layout = layout;

		GenVertexAttribPointers();

		m_Inserts = 0;
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
	}

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}

	void OpenGLVertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::InsertData(void* data, uint32_t size, uint32_t index)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferSubData(GL_ARRAY_BUFFER, index, size, data);
	}

	BufferLayout& OpenGLVertexBuffer::GetLayout()
	{
		return m_Layout;
	}

	void OpenGLVertexBuffer::SetLayout(BufferLayout newLayout)
	{
		m_Layout = newLayout;
		GenVertexAttribPointers();
	}

	void OpenGLVertexBuffer::GenVertexAttribPointers()
	{
		CH_PROFILE_FUNC();

		int i = 0;
		for (auto e : m_Layout.GetBufferElements())
		{
			
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(
				i,
				e.ComponentCount,
				ShaderDataTypeToGLType(e.Type),
				GL_FALSE,
				m_Layout.GetStride(),
				(const void*)e.Offset
			);
			i++;
		}
	}

	// INDEX BUFFER

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* data, uint32_t size)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), data, GL_STATIC_DRAW);

		m_Count = size;
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}

	void OpenGLIndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}
	uint32_t OpenGLIndexBuffer::GetCount()
	{
		return m_Count;
	}
}
