#pragma once

#include "Event.h"
#include "EventType.h"
#include "core/Application.h"

namespace Cherry
{

	class CHERRY_API EventListener
	{
	protected:
		EventListener(std::vector<EventType> types)
		{
			for (EventType type : types)
			{
				EventListeners[type].push_back(this);
			}
		};

	public:
		EventListener() {};
		virtual void OnEvent(Event e) = 0;

		static void InitEventListenerSystem();
		static std::unordered_map<EventType, std::vector<EventListener*>> EventListeners;
	};
}
