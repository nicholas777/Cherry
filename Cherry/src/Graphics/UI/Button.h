#pragma once

#include "core/Core.h"
#include "Math/Vector.h"
#include "Events/EventListener.h"
#include "UIComponent.h"
#include "Label.h"

namespace Cherry
{
	class CHERRY_API Button : public UIElement, public EventListener
	{
	public:
		using EventHandler = std::function<void(Event)>;

		Button(Label* label, Vector2f pos, Vector2f size, Vector4f color, const EventHandler& handler);

		virtual void OnEvent(Event e) override;
		virtual void OnUpdate() override;
	private:
		EventHandler m_Handler;
		Scoped<Label> m_Label;

		Vector2f m_Position, m_Size;
		Vector4f m_Color;
	};
}