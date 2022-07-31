#include "epch.h"
#include "Event.h"
#include "EventType.h"
#include "EventListener.h"
#include "core/Application.h"

std::unordered_map<Cherry::EventType, std::vector<Cherry::EventListener*>> Cherry::EventListener::EventListeners = std::unordered_map<Cherry::EventType, std::vector<Cherry::EventListener*>>();

void Cherry::EventListener::InitEventListenerSystem()
{
	EventType types[] = { EventType::Unknown,
		EventType::GameWarningEvent, EventType::GameErrorEvent,
		EventType::WindowCloseEvent, EventType::WindowOpenEvent, EventType::WindowResizeEvent, EventType::WindowFocusEvent, EventType::WindowUnfocusEvent,
		EventType::MouseClickEvent, EventType::MouseReleaseEvent, EventType::MouseMoveEvent, EventType::MouseScrollEvent,
		EventType::KeyPressEvent, EventType::KeyReleaseEvent };

	for (int i = 0; i < 16; i++)
	{
		EventListeners[types[i]] = std::vector<Cherry::EventListener*>();
	}
}
