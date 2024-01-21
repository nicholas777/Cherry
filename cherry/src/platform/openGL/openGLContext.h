#pragma once

#include "renderer/renderingContext.h"

class GLFWwindow;

namespace Cherry
{
    class OpenGLContext : public RenderingContext
    {
    public:
        OpenGLContext(GLFWwindow* window);

        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow* m_Window;
    };
}
