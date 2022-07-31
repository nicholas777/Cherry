#pragma once

#include <GLFW/glfw3.h>
#include "core/Window.h"
#include "Renderer/RenderingContext.h"

namespace Cherry
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(WindowData data);
		~WindowsWindow();

		virtual unsigned int GetWidth() const override { return m_Data.Width; };
		virtual unsigned int GetHeight() const override { return m_Data.Height; };

		virtual float GetTime() override;

		virtual void OnUpdate() override;
		virtual void OnResize(int, int) override;

		virtual void SetVSync(bool vsync) override;
		virtual bool IsVSync() const override { return m_Data.VSync; };

		virtual void* GetNativeWindow() override { return m_Window; };
	private:
		GLFWwindow* m_Window;
		WindowData m_Data;
		RenderingContext* m_Context;

		static void ErrorCallback(int error, const char* msg);
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		static void WindowResizeCallback(GLFWwindow* window, int width, int height);
		static void WindowCloseCallback(GLFWwindow* window);
		static void WindowFocusCallback(GLFWwindow* window, int focused);

	};
}
