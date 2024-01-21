#pragma once

#include "core/pointer.h"

namespace Cherry
{

    enum class ShaderDataType
    {
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

    class BufferElement
    {
    public:
        std::string Name;
        ShaderDataType Type;

        uint32_t Size;
        uint32_t Offset;
        uint32_t ComponentCount;
        
        BufferElement(std::string name, ShaderDataType type);

    private:
        void GenerateComponentCount();
    };

    class BufferLayout
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

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void InsertData(void* data, uint32_t count, uint32_t index) = 0;

        virtual BufferLayout& GetLayout() = 0;
        virtual void SetLayout(BufferLayout newLayout) = 0;

        static Scoped<VertexBuffer> Create(uint32_t count);
        static Scoped<VertexBuffer> Create(float* data, uint32_t count);
        static Scoped<VertexBuffer> Create(float* data, uint32_t count, BufferLayout layout);
    };
    
    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual uint32_t GetCount() = 0;

        static Scoped<IndexBuffer> Create(uint32_t* data, uint32_t size);
    };
}
