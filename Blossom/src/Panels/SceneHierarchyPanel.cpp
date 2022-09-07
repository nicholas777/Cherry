#include "SceneHierarchyPanel.h"

namespace Cherry
{
    SceneHierarchyPanel::SceneHierarchyPanel(Shared<Font> font)
        : UI({ 0.0f, 0.0f }, { 0.3f, 3.0f })
    {
        m_Color = Vector4f(0.2f, 0.2f, 0.2f, 1.0f);

        Label* label = new Label(font, "Click me", m_Position);
        label->SetScale(Vector2f(3.0f, 3.0f));

        Vector2f position = {
            m_Position.x + label->GetWidth() / 2,
            m_Position.y + label->GetHeight() / 2
        };

        Vector2f size = {
            label->GetWidth(),
            0.2f
        };

        m_Button = new Button(label, position, size, m_Color, &ButtonClickHandler);
    }

    SceneHierarchyPanel::~SceneHierarchyPanel()
    {
        m_Button.Free();
    }

    void SceneHierarchyPanel::OnUpdate()
    {
        m_Button->OnUpdate();
    }
}