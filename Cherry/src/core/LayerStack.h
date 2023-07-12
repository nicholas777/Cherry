#pragma once

#include "epch.h"
#include "Core.h"
#include "Layer.h"
#include "Pointer.h"

namespace Cherry
{
	class LayerStack
	{
	public:
		LayerStack() { m_Layers = std::vector<Layer*>(); };
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

		std::vector<Layer*>::reverse_iterator r_begin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator r_end() { return m_Layers.rend(); }

	private:
		std::vector<Layer*> m_Layers;
	};
}
