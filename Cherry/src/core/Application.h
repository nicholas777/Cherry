#pragma once

#include "Core.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Log.h"
#include "Window.h"
#include "Renderer/RenderAPI.h"
#include "ImGui/ImGuiRenderer.h"

namespace Cherry
{
	#define WINDOW_WIDTH (float)Application::GetApplication().GetWindow()->GetWidth()
	#define WINDOW_HEIGHT (float)Application::GetApplication().GetWindow()->GetHeight()

	class Application
	{
	public:
		struct ApplicationConfig
		{
			int WindowWidth = 600, WindowHeight = 400;
			std::string WindowTitle;
			bool IsVSync = true;

			std::string Name = "App";
		};

	public:
		Application();
		virtual ~Application();

		LayerStack& GetLayerStack() { return *m_LayerStack; };
		void PushLayer(Layer* layer) { m_LayerStack->PushLayer(layer); };
		
		void Run();

		void OnEvent(Event& e);
		void OnWindowClose();
		void OnWindowResize(int width, int height);

		static Application& GetApplication();
		Window* GetWindow();

	protected:
		ApplicationConfig Configuration;
	private:
		static Cherry::Application* s_Application;

		bool m_Running;
		LayerStack* m_LayerStack;
		Window* m_Window;

		ImGuiRenderer* m_ImGuiRenderer;

		float m_LastFrame = 0.0f;
	};

	// Defined by client
	Application* CreateApplication();
}
