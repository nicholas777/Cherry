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
		Application();
		~Application();

		bool isRunning;

		inline LayerStack& GetLayerStack() { return m_LayerStack; };

		void Run(void (*update)());
		static void Cherry::Application::OnEvent(Event* e);

		static void InitEngine();
		
		static Application& GetApplication();
		Window* GetWindow();
	private:
		static Cherry::Application* m_Game;
		static LayerStack m_LayerStack;
		Window* m_Window;
	};

	// Defined by the client
	void CHERRY_API OnStart();
	void CHERRY_API OnUpdate();
	void CHERRY_API OnShutdown();
}
