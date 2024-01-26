#pragma once

#include "core/application.h"
#include "event.h"
#include "eventType.h"

namespace Cherry {

    class EventListener
    {
    protected:
        EventListener(std::vector<EventType> types) {
            for (EventType type: types) { EventListeners[type].push_back(this); }
        };

    public:
        EventListener(){};
        virtual void OnEvent(const Event& e) = 0;

        static void InitEventListenerSystem();
        static std::unordered_map<EventType, std::vector<EventListener*>> EventListeners;
    };
}
