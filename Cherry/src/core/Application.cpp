#include "epch.h"
#include "Application.h"
#include "Events/EventListener.h"
#include "Events/EventType.h"
#include "Platform/Windows/WindowsInput.h"
#include "Events/Input.h"
#include "KeyCodes.h"
#include "Timestep.h"
#include "Platform/OpenGL/OpenGLTexture.h"

Cherry::Application* Cherry::Application::s_Application;

Cherry::Application::Application()
{
	Cherry::Log::Init();
	Cherry::EventListener::InitEventListenerSystem();

	Configuration = ApplicationConfig();
	m_LayerStack = new LayerStack;

	s_Application = this;
}

Cherry::Application::~Application()
{
	delete m_Window;
	delete m_LayerStack;
}

void Cherry::Application::Run()
{
	IsRunning = true;

	m_Window = Window::Create({ Configuration.WindowWidth, Configuration.WindowHeight, Configuration.WindowTitle, Configuration.IsVSync });

	Input::Init();

	for (auto layer : *m_LayerStack)
	{
		layer->OnAttach();
	}

	Timestep DeltaTime;

	while (IsRunning)
	{
		float time = m_Window->GetTime();
		DeltaTime = Timestep(time - m_LastFrame);
		m_LastFrame = time;

		m_Window->OnUpdate();

		for (Layer* layer : *m_LayerStack)
			layer->OnUpdate(DeltaTime);
	}
}

void Cherry::Application::OnEvent(Event* e)
{
	for (auto listener : *Cherry::EventListener::EventListeners[e->Type])
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

Cherry::Application& Cherry::Application::GetApplication()
{
	return *s_Application;
}

Cherry::Window* Cherry::Application::GetWindow()
{
	return m_Window;
}