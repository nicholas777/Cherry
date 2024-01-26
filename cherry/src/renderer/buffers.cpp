#include "buffers.h"

#include "core/log.h"
#include "epch.h"
#include "platform/openGL/openGLBuffers.h"
#include "renderAPI.h"

namespace Cherry {
    static uint32_t ShaderDataTypeToBytes(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Boolean: return 1;
            case ShaderDataType::Float: return 4;
            case ShaderDataType::Float2: return 8;
            case ShaderDataType::Float3: return 12;
            case ShaderDataType::Float4: return 16;
            case ShaderDataType::Mat3: return 36;
            case ShaderDataType::Mat4: return 64;
            case ShaderDataType::Int: return 4;
            case ShaderDataType::Int2: return 8;
            case ShaderDataType::Int3: return 12;
            case ShaderDataType::Int4: return 16;
            default:
                CH_ERROR("Unknows Data type!");
                CH_ASSERT(false, "Unknown data type!");
                return 0;
        }
    }

    BufferElement::BufferElement(std::string name, ShaderDataType type) {
        Name = name;
        Type = type;
        Size = ShaderDataTypeToBytes(type);
        Offset = 0;
        GenerateComponentCount();
    }

    void BufferElement::GenerateComponentCount() {
        switch (Type) {
            case ShaderDataType::Boolean: ComponentCount = 1; break;
            case ShaderDataType::Float: ComponentCount = 1; break;
            case ShaderDataType::Float2: ComponentCount = 2; break;
            case ShaderDataType::Float3: ComponentCount = 3; break;
            case ShaderDataType::Float4: ComponentCount = 4; break;
            case ShaderDataType::Mat3: ComponentCount = 9; break;
            case ShaderDataType::Mat4: ComponentCount = 16; break;
            case ShaderDataType::Int: ComponentCount = 1; break;
            case ShaderDataType::Int2: ComponentCount = 2; break;
            case ShaderDataType::Int3: ComponentCount = 3; break;
            case ShaderDataType::Int4: ComponentCount = 4; break;
        }
    }

    Scoped<VertexBuffer> VertexBuffer::Create(uint32_t size) {
        switch (RenderAPI::GetAPI()) {
            case RenderAPI::API::None:
                CH_ASSERT(false, "RenderAPI::API::None is not supported");
                return nullptr;
            case RenderAPI::API::OpenGL: return Scoped<VertexBuffer>(new OpenGLVertexBuffer(size));
        }

        return Scoped<VertexBuffer>(nullptr);
    }

    Scoped<VertexBuffer> VertexBuffer::Create(float* data, uint32_t size) {
        switch (RenderAPI::GetAPI()) {
            case RenderAPI::API::None:
                CH_ASSERT(false, "RenderAPI::API::None is not supported");
                return nullptr;
            case RenderAPI::API::OpenGL:
                return Scoped<VertexBuffer>(new OpenGLVertexBuffer(data, size));
        }

        return Scoped<VertexBuffer>(nullptr);
    }

    Scoped<VertexBuffer> VertexBuffer::Create(float* data, uint32_t size, BufferLayout layout) {
        switch (RenderAPI::GetAPI()) {
            case RenderAPI::API::None:
                CH_ASSERT(false, "RenderAPI::API::None is not supported");
                return nullptr;
            case RenderAPI::API::OpenGL:
                return Scoped<VertexBuffer>(new OpenGLVertexBuffer(data, size, layout));
        }

        return Scoped<VertexBuffer>(nullptr);
    }

    Scoped<IndexBuffer> IndexBuffer::Create(uint32_t* data, uint32_t size) {
        switch (RenderAPI::GetAPI()) {
            case RenderAPI::API::None:
                CH_ASSERT(false, "RenderAPI::API::None is not supported");
                return Scoped<IndexBuffer>(nullptr);
            case RenderAPI::API::OpenGL:
                return Scoped<IndexBuffer>(new OpenGLIndexBuffer(data, size));
        }

        return Scoped<IndexBuffer>(nullptr);
    }

}
