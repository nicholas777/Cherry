#pragma once

#include "epch.h"
#include "Core.h"
#include "Events/Event.h"
#include "core/Timestep.h"
#include "Pointer.h"

namespace Cherry
{
	class CHERRY_API Layer
	{
	public:

		Layer()
			: m_Name("Unknown") 
		{
		}

		Layer(const std::string& name) 
			: m_Name(name) 
		{
		}

		virtual ~Layer() {};

		std::string GetName() { return m_Name; }
		void SetName(const std::string& name) { m_Name = name; }

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(const Timestep& delta) {};
		virtual void OnEvent(Event* e) {};

	private:
		std::string m_Name;
	};
}
