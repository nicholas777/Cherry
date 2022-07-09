#include "epch.h"
#include "WindowsWindow.h"
#include "Core/Log.h"
#include "Events/EventListener.h"
#include "Events/Event.h"
#include "core/Application.h"

#include "glad/glad.h"

namespace Cherry
{
	static bool GLFWInit = false;

	static void ErrorCallback(int error, const char* msg) {
		Application::OnEvent(new GameErrorEvent((std::string("GLFW ERROR: ") + std::string(msg)).c_str()));
	}

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		switch (action)
		{
		case GLFW_PRESS:
			Application::OnEvent(new KeyPressEvent(key, false));
			break;
		case GLFW_RELEASE:
			Application::OnEvent(new KeyReleaseEvent(key));
			break;
		case GLFW_REPEAT:
			Application::OnEvent(new KeyPressEvent(key, true));
			break;
		}
	}

	static void MouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
	{
		Application::OnEvent(new MouseMoveEvent(int(xpos), int(ypos)));
	}

	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		switch (action)
		{
		case GLFW_PRESS:
			Application::OnEvent(new MouseClickEvent(button));
			break;
		case GLFW_RELEASE:
			Application::OnEvent(new MouseReleaseEvent(button));
			break;
		}
	}

	void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Application::OnEvent(new MouseScrollEvent(int(yoffset)));
	}

	void WindowCloseCallback(GLFWwindow* window)
	{
		Application::OnEvent(new WindowCloseEvent());
		Application::GetApplication().isRunning = false;
		CH_CORE_INFO("window closing");
	}

	void WindowResizeCallback(GLFWwindow* window, int width, int height)
	{
		Application::OnEvent(new WindowResizeEvent(width, height));
	}
	
	void WindowFocusCallback(GLFWwindow* window, int focused)
	{
		if (focused)
		{
			Application::OnEvent(new WindowFocusEvent());
		}
		else
		{
			Application::OnEvent(new WindowUnfocusEvent());
		}
	}

	WindowsWindow::WindowsWindow(WindowData data)
	{
		m_Data = data;

		if (!GLFWInit)
		{
			int result = glfwInit();
			CH_ASSERT(result, "Couldn't initialize GLFW");

			glfwSetErrorCallback(ErrorCallback);

			GLFWInit = true;
		}

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		Application::OnEvent(new WindowOpenEvent());

		CH_ASSERT(m_Window, "GLFW window is null");
		
		glfwMakeContextCurrent(m_Window);

		int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		SetVSync(true);

		// sets callback functions

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

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
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
