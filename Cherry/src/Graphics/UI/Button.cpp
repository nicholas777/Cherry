#include "epch.h"
#include "Button.h"
#include "Debug/Profiler.h"

namespace Cherry
{
	Button::Button(Label* label, Vector2f pos, Vector2f size, Vector4f color, const ClickEventHandler& handler)
		: EventListener({ EventType::MouseClickEvent })
	{
		m_Label = Scoped<Label>(label);
		m_Position = pos;
		m_Size = size;
		m_Color = color;

		m_Handler = handler;
	}

	void Button::OnEvent(Event& e)
	{
		CH_PROFILE_FUNC();
		// TODO: Coordinates for Renderer2D::DrawRect are the center of the rect
		MouseClickEvent& event = static_cast<MouseClickEvent&>(e);

		if (event.Button == MouseButton::ButtonLeft)
		{
			Vector2f mousePos = Input::GetMousePos();
			if (mousePos.x >= m_Position.x - m_Size.x / 2 &&
				mousePos.y <= m_Position.y + m_Size.y / 2 &&
				mousePos.x <= m_Position.x + m_Size.x / 2 &&
				mousePos.y >= m_Position.y - m_Size.y / 2)
			{
				m_Handler(event);
				event.handled = true;
			}
		}
	}

	void Button::OnUpdate()
	{
		CH_PROFILE_FUNC();
		Renderer2D::DrawRect(m_Position, m_Size, m_Color);
		m_Label->OnUpdate();
	}
}
