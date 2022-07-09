#include "epch.h"
#include "Application.h"
#include "../Events/EventListener.h"
#include "../Events/EventType.h"
#include "../Events/Input.h"
#include "Events/Input.h"
#include "KeyCodes.h"

Cherry::Application* Cherry::Application::m_Game;
Cherry::LayerStack Cherry::Application::m_LayerStack;

Cherry::Application::Application()
{
	CH_INFO("Entered Application constructor");
	isRunning = true;
}

Cherry::Application::~Application()
{
	delete m_Window;
}

void Cherry::Application::Run(void (*update)())
{
	m_Window = Window::Create(WindowData(600, 400, "Game Engine", true));
	Input::Init();

	while (isRunning)
	{
		m_Window->OnUpdate();
		update();

		CH_TRACE(Input::GetKeyPressed(Key::W) ? "w pressed" : "");

		for (Layer* layer : m_LayerStack)
			layer->OnUpdate();
	}

	delete m_Window;
}

void Cherry::Application::OnEvent(Event* e)
{
	for (auto listener : *Cherry::EventListener::EventListeners[e->Type])
	{
		listener->OnEvent(*e);
	}

	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
	{
		(**--it).OnEvent(e);

		if (e->handled)
			break;
	}

	delete e;
}

void Cherry::Application::InitEngine()
{
	Cherry::Log::Init();

	Cherry::EventListener::InitEventListenerSystem();
	m_Game = new Application();

}

Cherry::Application& Cherry::Application::GetApplication()
{
	return *m_Game;
}

Cherry::Window* Cherry::Application::GetWindow()
{
	return m_Window;
}