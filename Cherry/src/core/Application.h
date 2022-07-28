#pragma once

#include "Core.h"
#include "Layer.h"
#include "LayerStack.h"
#include "../Events/Event.h"
#include "Log.h"
#include "Window.h"

namespace Cherry
{

	// Application class, contains a representation 
	// of the Game
	
	class CHERRY_API Application
	{
	public:
		struct ApplicationConfig
		{
			int WindowWidth, WindowHeight;
			std::string WindowTitle;
			bool IsVSync;
		};

	public:
		Application();
		~Application();

		LayerStack& GetLayerStack() { return *m_LayerStack; };
		void PushLayer(Layer* layer) { m_LayerStack->PushLayer(layer); };

		void Run();
		void Cherry::Application::OnEvent(Event* e);

		static Application& GetApplication();
		Window* GetWindow();

		bool IsRunning;
	protected:
		ApplicationConfig Configuration;
	private:
		static Cherry::Application* s_Application;

		LayerStack* m_LayerStack;
		Window* m_Window;

		float m_LastFrame = 0.0f;
	};

	// Defined by client
	Application* CreateApplication();
}
