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
#include "Scripting/ScriptEngine.h"
#include "Debug/Profiler.h"

namespace Cherry
{
	// TODO: Fix warnings
	Application* Application::s_Application;

	Application::Application()
	{
		CH_PROFILE_FUNC();

		Log::Init();
		EventListener::InitEventListenerSystem();

		Configuration = ApplicationConfig();
		m_LayerStack = new LayerStack;

		m_ImGuiRenderer = new ImGuiRenderer;

		s_Application = this;
	}

	Application::~Application()
	{
		CH_PROFILE_FUNC();

		delete m_LayerStack;
		delete m_Window;
	}

	void Application::Startup()
	{
		CH_PROFILE_FUNC();

		m_Running = true;

		ScriptEngine::Init();

		m_Window = Window::Create({ Configuration.WindowWidth, Configuration.WindowHeight, Configuration.WindowTitle, Configuration.IsVSync });
		Renderer2D::Init();
		RenderCommand::Init();

		Input::Init();

		m_ImGuiRenderer->OnInit();

		for (auto layer : *m_LayerStack)
		{
			layer->OnAttach();
		}
	}

	void Application::Run()
	{
		CH_PROFILE_FUNC();

		Timestep DeltaTime;

		while (m_Running)
		{
			float time = (float)m_Window->GetTime();
			DeltaTime = Timestep(time - m_LastFrame);
			m_LastFrame = time;

			m_Window->OnUpdate();

			for (Layer* layer : *m_LayerStack)
				layer->OnUpdate(DeltaTime);

			m_ImGuiRenderer->Begin();
			for (Layer* layer : *m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiRenderer->End();
		}

		ScriptEngine::Shutdown();

		m_ImGuiRenderer->OnShutdown();
		delete m_ImGuiRenderer;

		Renderer2D::Shutdown();
	}

	void Application::OnEvent(Event& e)
	{
		CH_PROFILE_FUNC();

		for (auto listener : EventListener::EventListeners[e.Type])
		{
			listener->OnEvent(e);

			if (e.handled)
				break;
		}

		for (auto it = (*m_LayerStack).end(); it != (*m_LayerStack).begin();)
		{
			(**--it).OnEvent(e);

			if (e.handled)
				break;
		}
	}
	                                          
	void Application::OnWindowResize(int width, int height)
	{
		CH_PROFILE_FUNC();
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Application::OnWindowClose()
	{
		m_Running = false;
	}

	Application& Application::GetApplication()
	{
		return *s_Application;
	}

	Window* Application::GetWindow()
	{
		return m_Window;
	}
}
