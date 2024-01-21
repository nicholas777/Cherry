#include "epch.h"
#include "openGLContext.h"
#include "core/log.h"
#include "core/core.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Cherry
{
    OpenGLContext::OpenGLContext(GLFWwindow* window)
        : m_Window(window)
    {
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_Window);
        int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (!success) {
            CH_ERROR("Glad failed to load OpenGL");
            CH_ASSERT(success, "failed to load GLAD");
            return;
        }
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_Window);
    }
}
