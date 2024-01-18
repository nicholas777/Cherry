#include "epch.h"
#include "layerStack.h"

Cherry::LayerStack::~LayerStack()
{
	for (Layer* layer : m_Layers)
	{
		layer->OnDetach();
		delete layer;
	}
}

void Cherry::LayerStack::PushLayer(Layer* layer)
{
	m_Layers.push_back(layer);
}

void Cherry::LayerStack::PopLayer(Layer* layer)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);

	layer->OnDetach();
	m_Layers.erase(it);
}
