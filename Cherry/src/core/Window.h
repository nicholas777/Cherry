#pragma once

#include "Core.h"

namespace Cherry
{
	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;

		WindowData(int width, int height, std::string title, bool vsync)
			: Width(width), Height(height), Title(title), VSync(vsync) {};

		WindowData()
			: Width(600), Height(400), Title("Game"), VSync(true) {};
	};

	class CHERRY_API Window
	{
	public:
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetVSync(bool vsync) = 0;
		virtual bool IsVSync() const = 0;

		virtual float GetTime() = 0;

		virtual void OnUpdate() = 0;

		virtual void* GetNativeWindow() = 0;

		static Window* Create(WindowData data = WindowData());
	};
}