#include "epch.h"
#include "WindowsWindow.h"
#include "Core/Log.h"
#include "Events/EventListener.h"
#include "Events/Event.h"
#include "core/Application.h"
#include "Renderer/RenderCommand.h"

#include "core/KeyCodes.h"
#include "core/MouseButtonCodes.h"

namespace Cherry
{
	static bool GLFWInit = false;

	void WindowsWindow::ErrorCallback(int error, const char* msg) {
		Application::GetApplication().OnEvent(new GameErrorEvent((std::string("GLFW ERROR: ") + std::string(msg)).c_str()));
	}

	void WindowsWindow::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		switch (action)
		{
		case GLFW_PRESS:
			Application::GetApplication().OnEvent(new KeyPressEvent(static_cast<Key>(key), false));
			break;
		case GLFW_RELEASE:
			Application::GetApplication().OnEvent(new KeyReleaseEvent(static_cast<Key>(key)));
			break;
		case GLFW_REPEAT:
			Application::GetApplication().OnEvent(new KeyPressEvent(static_cast<Key>(key), true));
			break;
		}
	}

	void WindowsWindow::MouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
	{
		Application::GetApplication().OnEvent(new MouseMoveEvent(int(xpos), int(ypos)));
	}

	void WindowsWindow::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		switch (action)
		{
		case GLFW_PRESS:
			Application::GetApplication().OnEvent(new MouseClickEvent(static_cast<MouseButton>(button)));
			break;
		case GLFW_RELEASE:
			Application::GetApplication().OnEvent(new MouseReleaseEvent(static_cast<MouseButton>(button)));
			break;
		}
	}

	void WindowsWindow::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Application::GetApplication().OnEvent(new MouseScrollEvent(yoffset));
	}

	void WindowsWindow::WindowCloseCallback(GLFWwindow* window)
	{
		Application::GetApplication().OnEvent(new WindowCloseEvent);
		Application::GetApplication().OnWindowClose();
		CH_CORE_INFO("window closing");
	}

	void WindowsWindow::WindowResizeCallback(GLFWwindow* window, int width, int height)
	{
		Application::GetApplication().OnEvent(new WindowResizeEvent(width, height));
		Application::GetApplication().OnWindowResize(width, height);
	}
	
	void WindowsWindow::WindowFocusCallback(GLFWwindow* window, int focused)
	{
		if (focused)
		{
			Application::GetApplication().OnEvent(new WindowFocusEvent());
		}
		else
		{
			Application::GetApplication().OnEvent(new WindowUnfocusEvent());
		}
	}

	WindowsWindow::WindowsWindow(WindowData data)
	{
		m_Data = data;

		if (!GLFWInit)
		{
			int result = glfwInit();
			CH_ASSERT(result, "Couldn't initialize GLFW");

			glfwSetErrorCallback(WindowsWindow::ErrorCallback);

			GLFWInit = true;
		}

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		m_Context = RenderingContext::Create(m_Window);
		m_Context->Init();

		Application::GetApplication().OnEvent(new WindowOpenEvent());

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
	
	WindowsWindow::~WindowsWindow()
	{
		delete m_Window;
	}

	float WindowsWindow::GetTime()
	{
		return glfwGetTime();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::OnResize(int width, int height)
	{
		m_Data.Width = width;
		m_Data.Height = height;

		RenderCommand::SetViewport(0, 0, width, height);
	}

	void WindowsWindow::SetVSync(bool vsync)
	{
		if (vsync)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = vsync;
	}
}

#ifdef CH_PLATFORM_WINDOWS
	Cherry::Window* Cherry::Window::Create(WindowData data)
	{
		return new WindowsWindow(data);
	}
#endif
