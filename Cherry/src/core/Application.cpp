#include "epch.h"
#include "Application.h"
#include "Events/EventListener.h"
#include "Events/EventType.h"
#include "Platform/Windows/WindowsInput.h"
#include "Events/Input.h"
#include "KeyCodes.h"
#include "Timestep.h"
#include "Pointer.h"
#include "Renderer/Renderer2D.h"

namespace Cherry
{
	Application* Application::s_Application;

	Application::Application()
	{
		EventListener::InitEventListenerSystem();

		Configuration = ApplicationConfig();
		m_LayerStack = new LayerStack;

		s_Application = this;
	}

	Application::~Application()
	{
		Renderer2D::Shutdown();

		delete m_Window;
		delete m_LayerStack;
	}

	void Application::Run()
	{
		m_Running = true;

		Log::Init(Configuration.Name);

		m_Window = Window::Create({ Configuration.WindowWidth, Configuration.WindowHeight, Configuration.WindowTitle, Configuration.IsVSync });
		Renderer2D::Init();
		RenderCommand::Init();

		Input::Init();

		for (auto layer : *m_LayerStack)
		{
			layer->OnAttach();
		}

		Timestep DeltaTime;

		while (m_Running)
		{
			float time = m_Window->GetTime();
			DeltaTime = Timestep(time - m_LastFrame);
			m_LastFrame = time;

			m_Window->OnUpdate();

			for (Layer* layer : *m_LayerStack)
				layer->OnUpdate(DeltaTime);
		}
	}

	void Application::OnEvent(Event* e)
	{
		for (auto listener : EventListener::EventListeners[e->Type])
		{
			listener->OnEvent(*e);
		}

		for (auto it = (*m_LayerStack).end(); it != (*m_LayerStack).begin();)
		{
			(**--it).OnEvent(e);

			if (e->handled)
				break;
		}

		delete e;
	}
	void Application::OnWindowResize(int width, int height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Application::OnWindowClose()
	{
		m_Running = false;
	}

	Window* Application::GetWindow()
	{
		return m_Window;
	}

	Application& Application::GetApplication()
	{
		return *s_Application;
	}
}
