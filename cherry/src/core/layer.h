#pragma once

#include "events/event.h"
#include "timestep.h"

namespace Cherry
{
	class Layer
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
		virtual void OnUpdate(const Timestep& delta) = 0;
		virtual void OnImGuiRender() {};
		virtual void OnEvent(Event& e) = 0;

	private:
		std::string m_Name;
	};
}
