#pragma once

#include "epch.h"
#include "Core.h"
#include "Events/Event.h"
#include "core/Timestep.h"

namespace Cherry
{
	class CHERRY_API Layer
	{
	public:

		Layer()
			: m_Name("Unknows") 
		{
		}

		Layer(std::string name) 
			: m_Name(name) 
		{
		}

		virtual ~Layer() {};

		std::string GetName() { return m_Name; }
		void SetName(std::string name) { m_Name = name; }

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(Timestep delta) {};
		virtual void OnEvent(Event* e) {};

	private:
		std::string m_Name;
	};
}
