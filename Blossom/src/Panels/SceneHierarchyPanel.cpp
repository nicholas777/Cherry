#include "SceneHierarchyPanel.h"
#include "core/MouseButtonCodes.h"
#include "EditorLayer.h"
#include "core/Log.h"

#include <math.h>

namespace Cherry
{
    SceneHierarchyPanel::SceneHierarchyPanel(Vector2f pos, Vector2f size, Shared<Font> font, Shared<Scene> scene)
        : UI({ pos }, size), m_Scene(scene), m_Font(font),
          EventListener({ EventType::MouseClickEvent })
    {
        m_Color = Vector4f(0.2f, 0.2f, 0.2f, 1.0f);
        m_LineSize = m_Font->GetFontSize() / WINDOW_HEIGHT;

        Entity e1 = m_Scene->CreateEntity("Entity");
        Entity e2 = m_Scene->CreateEntity("Entity");
        Entity e3 = m_Scene->CreateEntity("Entity");
        Entity e4 = m_Scene->CreateEntity("Entity");
        Entity e5 = m_Scene->CreateEntity("Entity");
        Entity e6 = m_Scene->CreateEntity("Entity");
        Entity e7 = m_Scene->CreateEntity("Entity");
        Entity e8 = m_Scene->CreateEntity("Entity");
    }

    SceneHierarchyPanel::~SceneHierarchyPanel()
    {
        
    }

    void SceneHierarchyPanel::SetScene(Shared<Scene> scene)
    {
        m_Scene = scene;
    }

    void SceneHierarchyPanel::OnUpdate()
    {
        float index = 0.0f;
        Renderer2D::DrawRect(m_Position, m_Size, m_Color);
        m_Font->RenderText({ m_Position.x - m_Size.x * 0.8f, m_Position.y + m_Size.y * 0.9f }, "Scene Hierarchy");

        for (int i = 0; i < m_Scene->m_Registry.size(); i++)
        {
            auto& name = m_Scene->m_Registry.get<NameComponent>(m_Scene->m_Registry.data()[i]); 
            m_Font->RenderText({ m_Position.x - m_Size.x * 0.8f, m_Position.y + m_Size.y * 0.7f - index }, name.Name);
            index += m_LineSize;
        }

    }

    void SceneHierarchyPanel::OnEvent(Event& event)
    {
        MouseClickEvent& clickEvent = static_cast<MouseClickEvent&>(event);

        if (clickEvent.Button == MouseButton::ButtonLeft)
        {
            Vector2f mousePos = Input::GetMousePos();
            if (mousePos.x >= m_Position.x &&
                mousePos.x <= m_Position.x + m_Size.x * 2 &&
                mousePos.y <= m_Position.y + m_Size.y - m_LineSize &&
                mousePos.y >= m_Position.y + m_Size.y * 0.7f - m_LineSize * (m_Scene->m_Registry.size() + 1))
            {
                float a = m_Position.y + m_Size.y - m_LineSize;

                int entityNumber = floor(10 * abs(a - (a - (mousePos.y - a)))) - 1;
                
                CH_ASSERT(m_Scene->m_Registry.size() >= entityNumber, "error: wierd shit is happening");
                
                Entity e = Entity(m_Scene->m_Registry.data()[entityNumber], m_Scene.Get());
                CH_INFO(e.GetComponent<NameComponent>().Name);

                EditorLayer::SelectEntity(e);

                event.handled = true;
            }
        }
    }
}
