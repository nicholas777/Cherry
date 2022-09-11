#pragma once

#include "Cherry.h"

namespace Cherry
{
	class PropertiesPanel
	{
	public:
		PropertiesPanel();
		
		void SetEntity(const Entity& e);
		void OnUpdate();

	private:
		Entity m_Current;
	};
}
