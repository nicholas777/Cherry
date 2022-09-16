#include "PropertiesPanel.h"

namespace Cherry
{
    PropertiesPanel::PropertiesPanel()
    {

    }

    void PropertiesPanel::SetEntity(const Entity& e)
    {
        m_Current = e;
        if (m_Current.HasComponent<SpriteComponent>())
        {
            m_UseTexture = m_Current.GetComponent<SpriteComponent>().SpriteTexture.IsAlive();
        }
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

        if (!m_Current.IsValid())
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

        if (m_Current.HasComponent<SpriteComponent>())
        {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow;
            if (ImGui::TreeNodeEx((void*)2, flags, "Sprite Component"))
            {
                SpriteComponent& sprite = m_Current.GetComponent<SpriteComponent>();
                

                int useTexture;
                if (ImGui::RadioButton("Use color", &useTexture, 0))
                {
                    if (useTexture == 0)
                    {
                        m_UseTexture = false;
                        sprite.UseTexture = false;
                    }
                    else
                    {
                        m_UseTexture = true;
                        sprite.UseTexture = true;
                    }
                }

                ImGui::SameLine();

                if (ImGui::RadioButton("Use texture", &useTexture, 1))
                {
                    if (useTexture == 0)
                    {
                        m_UseTexture = false;
                        sprite.UseTexture = false;
                    }
                    else
                    {
                        m_UseTexture = true;
                        sprite.UseTexture = true;
                    }
                }

                if (!m_UseTexture)
                {
                    float buffer[4] = {
                        sprite.Color.x,
                        sprite.Color.y,
                        sprite.Color.z,
                        sprite.Color.w
                    };

                    if (ImGui::ColorEdit4("Color", buffer))
                    {
                        sprite.Color = buffer;
                    }
                }
                else
                {
                    if (!sprite.SpriteTexture.IsAlive())
                    {
                        ImGui::Text("This entity doesn't have a texture attached");
                        ImGui::TreePop();
                        ImGui::End();
                        return;
                    }

                    ImGui::Text("Texture");
                    ImGui::Image((void*)sprite.SpriteTexture->GetTextureID(), ImVec2(160.0f, 160.0f), ImVec2(0, 1), ImVec2(1, 0));
                }

                ImGui::TreePop();
            }
        }

        if (m_Current.HasComponent<CameraComponent>())
        {
            // TODO: Camera component view
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow;
            if (ImGui::TreeNodeEx((void*)2, flags, "Camera Component"))
            {
                ImGui::Text("Camera components are not \nimplemented yet!");
                ImGui::TreePop();
            }
        }

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow;
        if (ImGui::TreeNodeEx((void*)3, flags, "Component Browser"))
        {
            if (ImGui::BeginListBox("Components"))
            {
                bool selected = true;
                if (ImGui::Selectable("TransformComponent", &selected))
                {
                    if (!m_Current.HasComponent<TransformComponent>())
                        m_Current.AddComponent<TransformComponent>();
                }

                if (ImGui::Selectable("SpriteComponent", &selected))
                {
                    if (!m_Current.HasComponent<SpriteComponent>())
                        m_Current.AddComponent<SpriteComponent>();
                }

                if (ImGui::Selectable("CameraComponent", &selected))
                {
                    if (!m_Current.HasComponent<CameraComponent>())
                        m_Current.AddComponent<CameraComponent>();
                }

                if (ImGui::Selectable("ScriptExecutorComponent", &selected))
                {
                    if (!m_Current.HasComponent<ScriptComponent>())
                    {
                        // m_Current.AddComponent<ScriptComponent>();
                    }
                }

                ImGui::EndListBox();
            }

            ImGui::TreePop();
        }

        ImGui::End();
        
    }

}
