#include "PropertiesPanel.h"

namespace Cherry
{
    PropertiesPanel::PropertiesPanel()
    {
        
    }

    void PropertiesPanel::SetEntity(const Entity& e)
    {
        m_Current = e;
    }
    
    void PropertiesPanel::OnUpdate()
    {
        if (!m_Current)
        {
            ImGui::Begin("Properties");
            ImGui::Text("No entity selected!");
            ImGui::End();
            return;
        }
            

        ImGui::Begin("Properties");

        if (m_Current.HasComponent<NameComponent>())
        {
            auto& name = m_Current.GetComponent<NameComponent>();

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow;
            if (ImGui::TreeNodeEx((void*)0, flags, "Name Component"))
            {
                char str[128];
                memset(str, 0, sizeof(str));
                strcpy(str, name.Name.c_str());

                if (ImGui::InputText("Name", str, sizeof(str)))
                {
                    name.Name = str;
                }

                ImGui::TreePop();
            }
        }
        
        if (m_Current.HasComponent<TransformComponent>())
        {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow;
            if (ImGui::TreeNodeEx((void*)1, flags, "Transform"))
            {

                TransformComponent& transform = m_Current.GetComponent<TransformComponent>();

                float translation[2] = {
                    transform.Translation.x,
                    transform.Translation.y
                };

                if (ImGui::InputFloat2("Translation", translation))
                {
                    transform.Translation = translation;
                }

                float rotation = transform.Rotation;
                if (ImGui::InputFloat("Rotation", &rotation))
                {
                    transform.Rotation = rotation;
                }

                float scale[2] = {
                    transform.Scale.x,
                    transform.Scale.y
                };

                if (ImGui::InputFloat2("Scale", scale))
                {
                    transform.Scale = scale;
                }

                ImGui::TreePop();
            }
        }

        ImGui::End();
    }

}
