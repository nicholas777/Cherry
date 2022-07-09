#pragma once

#include "epch.h"
#include "Core.h"
#include "Events/Event.h"

namespace Cherry
{
	class CHERRY_API Layer
	{
	public:

		Layer() {};
		virtual ~Layer() {};

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnEvent(Event* e) = 0;

	};
}
