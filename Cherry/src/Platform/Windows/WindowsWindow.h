#pragma once

#include <GLFW/glfw3.h>
#include "core/Window.h"
#include "Platform/OpenGL/OpenGLContext.h"

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

		virtual void SetVSync(bool vsync) override;
		virtual bool IsVSync() const override { return m_Data.VSync; };

		virtual void* GetNativeWindow() override { return m_Window; };
	private:
		GLFWwindow* m_Window;
		WindowData m_Data;
		OpenGLContext* m_Context;
	};
}
