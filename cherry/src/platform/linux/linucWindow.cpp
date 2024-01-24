#include "epch.h"
#include "linuxWindow.h"
#include "core/log.h"
#include "events/eventListener.h"
#include "events/event.h"
#include "core/application.h"
#include "renderer/renderCommand.h"

#include "core/keyCodes.h"
#include "core/mouseButtonCodes.h"

namespace Cherry
{
    static bool GLFWInit = false;

    void LinuxWindow::ErrorCallback(int error, const char* msg) {
        Application::GetApplication().OnEvent(GameErrorEvent((std::string("GLFW ERROR: ") + std::string(msg)).c_str()));
    }

    void LinuxWindow::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        switch (action)
        {
        case GLFW_PRESS:
            Application::GetApplication().OnEvent(KeyPressEvent(static_cast<Key>(key), false));
            break;
        case GLFW_RELEASE:
            Application::GetApplication().OnEvent(KeyReleaseEvent(static_cast<Key>(key)));
            break;
        case GLFW_REPEAT:
            Application::GetApplication().OnEvent(KeyPressEvent(static_cast<Key>(key), true));
            break;
        }
    }

    void LinuxWindow::MouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
    {
        Application::GetApplication().OnEvent(MouseMoveEvent(int(xpos), int(ypos)));
    }

    void LinuxWindow::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        switch (action)
        {
        case GLFW_PRESS:
            Application::GetApplication().OnEvent(MouseClickEvent(static_cast<MouseButton>(button)));
            break;
        case GLFW_RELEASE:
            Application::GetApplication().OnEvent(MouseReleaseEvent(static_cast<MouseButton>(button)));
            break;
        }
    }

    void LinuxWindow::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
    {
        Application::GetApplication().OnEvent(MouseScrollEvent((int)yoffset));
    }

    void LinuxWindow::WindowCloseCallback(GLFWwindow* window)
    {
        Application::GetApplication().OnEvent(WindowCloseEvent());
        Application::GetApplication().OnWindowClose();
        CH_INFO("window closing");
    }

    void LinuxWindow::WindowResizeCallback(GLFWwindow* window, int width, int height)
    {
        Application::GetApplication().OnEvent(WindowResizeEvent(width, height));
        Application::GetApplication().OnWindowResize(width, height);
    }
    
    void LinuxWindow::WindowFocusCallback(GLFWwindow* window, int focused)
    {
        if (focused)
        {
            Application::GetApplication().OnEvent(WindowFocusEvent());
        }
        else
        {
            Application::GetApplication().OnEvent(WindowUnfocusEvent());
        }
    }

    LinuxWindow::LinuxWindow(WindowData data)
    {
        m_Data = data;

        if (!GLFWInit)
        {
            int result = glfwInit();
            CH_ASSERT(result, "Couldn't initialize GLFW");

            glfwSetErrorCallback(LinuxWindow::ErrorCallback);

            GLFWInit = true;
        }

        m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
        m_Context = RenderingContext::Create(m_Window);
        m_Context->Init();

        Application::GetApplication().OnEvent(WindowOpenEvent());

        CH_ASSERT(m_Window, "GLFW window is null");
        SetVSync(true);

        // callback functions

        glfwSetKeyCallback(m_Window, KeyCallback);
        glfwSetCursorPosCallback(m_Window, MouseMoveCallback);
        glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
        glfwSetScrollCallback(m_Window, ScrollCallback);
        glfwSetWindowSizeCallback(m_Window, WindowResizeCallback);
        glfwSetWindowCloseCallback(m_Window, WindowCloseCallback);
        glfwSetWindowFocusCallback(m_Window, WindowFocusCallback);
    }
    
    LinuxWindow::~LinuxWindow()
    {
        delete m_Window;
    }

    double LinuxWindow::GetTime()
    {
        return glfwGetTime();
    }

    void LinuxWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void LinuxWindow::OnResize(int width, int height)
    {
        m_Data.Width = width;
        m_Data.Height = height;

        RenderCommand::SetViewport(0, 0, width, height);
    }

    void LinuxWindow::SetVSync(bool vsync)
    {
        if (vsync)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = vsync;
    }
}

Cherry::Window* Cherry::Window::Create(WindowData data)
{
    return new LinuxWindow(data);
}
