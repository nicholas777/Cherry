#include "event.h"

#include "core/application.h"
#include "debug/profiler.h"
#include "epch.h"
#include "eventListener.h"
#include "eventType.h"

std::unordered_map<Cherry::EventType, std::vector<Cherry::EventListener*>>
    Cherry::EventListener::EventListeners =
        std::unordered_map<Cherry::EventType, std::vector<Cherry::EventListener*>>();

void Cherry::EventListener::InitEventListenerSystem() {
    CH_PROFILE_FUNC();

    std::vector<EventType> types = { EventType::Unknown,          EventType::GameWarningEvent,
                                     EventType::GameErrorEvent,   EventType::WindowCloseEvent,
                                     EventType::WindowOpenEvent,  EventType::WindowResizeEvent,
                                     EventType::WindowFocusEvent, EventType::WindowUnfocusEvent,
                                     EventType::MouseClickEvent,  EventType::MouseReleaseEvent,
                                     EventType::MouseMoveEvent,   EventType::MouseScrollEvent,
                                     EventType::KeyPressEvent,    EventType::KeyReleaseEvent };

    for (int i = 0; i < types.size(); i++) {
        EventListeners[types[i]] = std::vector<Cherry::EventListener*>();
    }
}
