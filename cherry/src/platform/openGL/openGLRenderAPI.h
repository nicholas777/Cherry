#pragma once

#include "renderer/renderAPI.h"
#include "renderer/vertexArray.h"

#include <glad/gl.h>

namespace Cherry {
    class OpenGLRenderAPI : public RenderAPI
    {
    public:
        virtual void Init() override;

        virtual void SetViewport(int x, int y, int width, int height) override;

        virtual void SetClearColor(Vector4f color) override;
        virtual void Clear() override;

        virtual void DrawElements(VertexArray* vao, uint32_t indexCount) override;
    };
}
