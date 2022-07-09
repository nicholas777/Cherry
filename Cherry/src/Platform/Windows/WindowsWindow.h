#pragma once

#include <GLFW/glfw3.h>
#include "core/Window.h"

namespace Cherry
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(WindowData data);
		~WindowsWindow();

		inline unsigned int GetWidth() const override { return m_Data.Width; };
		inline unsigned int GetHeight() const override { return m_Data.Height; };

		void OnUpdate() override;

		inline void SetVSync(bool vsync) override;
		inline bool IsVSync() const override { return m_Data.VSync; };

		virtual void* GetNativeWindow() override { return m_Window; };
	private:
		GLFWwindow* m_Window;
		WindowData m_Data;
	};
}
