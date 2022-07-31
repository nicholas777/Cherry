#pragma once

#include "core/Core.h"
#include "core/Log.h"

#include <cstdint>
#include <vector>
#include <string>

namespace Cherry
{

	enum class CHERRY_API ShaderDataType
	{
		Unknows = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Boolean,
	};

	static uint32_t ShaderDataTypeToBytes(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Boolean:
			return 1;
		case ShaderDataType::Float:
			return 4;
		case ShaderDataType::Float2:
			return 8;
		case ShaderDataType::Float3:
			return 12;
		case ShaderDataType::Float4:
			return 16;
		case ShaderDataType::Mat3:
			return 36;
		case ShaderDataType::Mat4:
			return 64;
		case ShaderDataType::Int:
			return 4;
		case ShaderDataType::Int2:
			return 8;
		case ShaderDataType::Int3:
			return 12;
		case ShaderDataType::Int4:
			return 16;
		default:
			CH_ERROR("Unknows Data type!");
			CH_ASSERT(false, "Unknown data type!");
		}
	}

	// TODO: Fix copying
	class CHERRY_API BufferElement
	{
	public:
		std::string Name;
		ShaderDataType Type;

		uint32_t Size;
		uint32_t Offset;
		uint32_t ComponentCount;
		
		BufferElement(std::string name, ShaderDataType type)
			:	Name(name), 
				Type(type), 
				Size(ShaderDataTypeToBytes(type)),
				Offset(0)
		{
			GenerateComponentCount();
		}

	private:
		void GenerateComponentCount()
		{
			switch (Type)
			{
			case ShaderDataType::Boolean:	ComponentCount = 1;  break;
			case ShaderDataType::Float:		ComponentCount = 1;	 break;
			case ShaderDataType::Float2:	ComponentCount = 2;	 break;
			case ShaderDataType::Float3:	ComponentCount = 3;	 break;
			case ShaderDataType::Float4:	ComponentCount = 4;	 break;
			case ShaderDataType::Mat3:		ComponentCount = 9;	 break;
			case ShaderDataType::Mat4:		ComponentCount = 16; break;
			case ShaderDataType::Int:		ComponentCount = 1;	 break;
			case ShaderDataType::Int2:		ComponentCount = 2;	 break;
			case ShaderDataType::Int3:		ComponentCount = 3;	 break;
			case ShaderDataType::Int4:		ComponentCount = 4;	 break;
			default: 
				CH_ERROR("Unknown data type!");
				CH_ASSERT(false, "Unknows data type!");
			}
		}
	};

	class CHERRY_API BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(std::initializer_list<BufferElement> elements)
			: m_BufferElements(elements)
		{
			m_Stride = 0;
			for (BufferElement& e : m_BufferElements)
			{
				e.Offset = m_Stride;
				m_Stride += e.Size;
			}
		}

		inline int GetStride() { return m_Stride; }
		inline std::vector<BufferElement> GetBufferElements() { return m_BufferElements; };
	private:
		uint32_t m_Stride = 0;
		std::vector<BufferElement> m_BufferElements;
	};

	class CHERRY_API VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual BufferLayout& GetLayout() = 0;
		virtual void SetLayout(BufferLayout newLayout) = 0;

		static VertexBuffer* Create(float* data, uint32_t size, BufferLayout layout);
	};
	
	class CHERRY_API IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual uint32_t GetCount() = 0;

		static IndexBuffer* Create(uint32_t* data, uint32_t size);
	};
}