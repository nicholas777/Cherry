#pragma once

#include "math/vector.h"
#include "events/eventListener.h"
#include "uiComponent.h"
#include "label.h"

namespace Cherry
{
    class Button : public UIElement, public EventListener
    {
    public:
        using ClickEventHandler = std::function<void(const MouseClickEvent&)>;

        Button(Label* label, Vector2f pos, Vector2f size, Vector4f color, const ClickEventHandler& handler);

        virtual void OnEvent(const Event& e) override;
        virtual void OnUpdate() override;
    private:
        ClickEventHandler m_Handler;
        Scoped<Label> m_Label;

        Vector2f m_Position, m_Size;
        Vector4f m_Color;
    };
}
