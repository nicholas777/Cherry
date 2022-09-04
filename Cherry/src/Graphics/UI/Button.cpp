#include "epch.h"
#include "Button.h"

namespace Cherry
{
	Button::Button(Label* label, Vector2f pos, Vector2f size, Vector4f color, const EventHandler& handler)
	{
		m_Label = Scoped<Label>(label);
		m_Position = pos;
		m_Size = size;
		m_Color = color;

		m_Handler = handler;
	}

	void Button::OnEvent(Event e)
	{
	}

	void Button::OnUpdate()
	{
	}
}