#pragma once

#include "epch.h"
#include "Core.h"
#include "Layer.h"

namespace Cherry
{
	class CHERRY_API LayerStack
	{
	public:
		LayerStack() {};
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

		std::vector<Layer*>::iterator r_begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator r_end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
	};
}
