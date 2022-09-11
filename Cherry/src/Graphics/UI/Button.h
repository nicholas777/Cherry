#pragma once

#include "core/Core.h"
#include "Math/Vector.h"
#include "Events/EventListener.h"
#include "UIComponent.h"
#include "Label.h"
#include "core/MouseButtonCodes.h"
#include "Events/Input.h"
#include "Renderer/Renderer2D.h"

namespace Cherry
{
	class Button : public UIElement, public EventListener
	{
	public:
		using ClickEventHandler = std::function<void(const MouseClickEvent&)>;

		Button(Label* label, Vector2f pos, Vector2f size, Vector4f color, const ClickEventHandler& handler);

		virtual void OnEvent(Event& e) override;
		virtual void OnUpdate() override;
	private:
		ClickEventHandler m_Handler;
		Scoped<Label> m_Label;

		Vector2f m_Position, m_Size;
		Vector4f m_Color;
	};
}