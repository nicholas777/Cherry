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

        m_Mode = 0;
    }

    void PropertiesPanel::SetAsset(Asset* a)
    {
        m_Asset = a;
        m_Mode = 1;
    }

    void PropertiesPanel::OnUpdate()
    {
        if (m_Mode == 0)
            DrawEntity();
        else
            DrawAsset();
    }

    void PropertiesPanel::DrawEntity()
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
                    }
                    else
                    {
                        ImGui::Text("Texture");
                        ImGui::Image(
                            (void*)sprite.SpriteTexture->GetTextureID(), 
                            ImVec2(160.0f, 160.0f), ImVec2(0, 1), 
                            ImVec2(1, 0));
                    }

                    if (ImGui::BeginDragDropTarget())
                    {
                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("AssetTexture"))
                        {
                            CH_ASSERT(payload->DataSize == sizeof(TextureAsset), "help idk what this error is");
                            sprite.SpriteTexture = (*(const TextureAsset*)payload->Data).ptr;
                        }

                        ImGui::EndDragDropTarget();
                    }
                }

                ImGui::TreePop();
            }
        }

        if (m_Current.HasComponent<CameraComponent>())
        {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow;
            if (ImGui::TreeNodeEx((void*)2, flags, "Camera Component"))
            {
                CameraComponent& comp = m_Current.GetComponent<CameraComponent>();

                ImGui::Checkbox("Primary", &comp.IsPrimary);

                float span = comp.camera.GetSpan();
                if (ImGui::InputFloat("Span", &span))
                {
                    comp.camera.SetSpan(span);
                    comp.camera.RecelcProjection();
                }

                float znear = comp.camera.GetNear();
                if (ImGui::InputFloat("Near plane", &znear))
                {
                    comp.camera.SetNear(znear);
                    comp.camera.RecelcProjection();
                }

                float zfar = comp.camera.GetFar();
                if (ImGui::InputFloat("Near plane", &zfar))
                {
                    comp.camera.SetFar(zfar);
                    comp.camera.RecelcProjection();
                }

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

    void PropertiesPanel::DrawAsset()
    {
        if (m_Asset == nullptr)
        {
            ImGui::Begin("Properties");
            ImGui::Text("Invalid Asset!");
            ImGui::End();
            return;
        }

        if (m_Asset->type == AssetType::Unknown)
        {
            ImGui::Begin("Properties");
            ImGui::Text("Invalid asset!");
            ImGui::End();
            return;
        }

        ImGui::Begin("Properties");

        if (m_Asset->type == AssetType::Texture)
        {
            TextureAsset* asset = (TextureAsset*)m_Asset;

            const char* items[] = { "Repeat", "Mirrored Repeat", "Clamp to Edge", "Clamp to Border" };
            if (ImGui::BeginCombo("Wrap", items[(int)asset->params.wrap - 1]))
            {
                for (int i = 0; i < IM_ARRAYSIZE(items); i++)
                {
                    bool selected = i == (int)asset->params.wrap - 1;
                    if (ImGui::Selectable(items[i], selected))
                    {
                        asset->params.wrap = static_cast<TextureWrap>(i + 1);
                        asset->ptr->ResetParams(asset->params);
                    }

                    if (selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            const char* items3[] = { "Nearest", "Linear" };
            if (ImGui::BeginCombo("Min-Filter", items3[(int)asset->params.minFilter - 1]))
            {
                for (int i = 0; i < IM_ARRAYSIZE(items3); i++)
                {
                    bool selected = i == (int)asset->params.minFilter - 1;
                    if (ImGui::Selectable(items3[i], selected))
                    {
                        asset->params.minFilter = static_cast<TextureFilter>(i + 1);
                        asset->ptr->ResetParams(asset->params);
                    }

                    if (selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            const char* items4[] = { "Nearest", "Linear" };
            if (ImGui::BeginCombo("Mag-Filter", items4[(int)asset->params.magFilter - 1]))
            {
                for (int i = 0; i < IM_ARRAYSIZE(items4); i++)
                {
                    bool selected = i == (int)asset->params.magFilter - 1;
                    if (ImGui::Selectable(items4[i], selected))
                    {
                        asset->params.magFilter = static_cast<TextureFilter>(i + 1);
                        asset->ptr->ResetParams(asset->params);
                    }

                    if (selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            const char* items2[] = { "RGBA", "RGB", "Luminance", "Luminance with Alpha", "Depth24Stencil8", "Auto" };
            if (ImGui::BeginCombo("Format", items2[(int)asset->params.format - 1]))
            {
                for (int i = 0; i < IM_ARRAYSIZE(items2); i++)
                {
                    bool selected = i == (int)asset->params.format - 1;
                    if (ImGui::Selectable(items2[i], selected))
                    {
                        asset->params.format = static_cast<TextureFormat>(i + 1);
                        asset->ptr = Texture::Create(asset->filepath, asset->params);
                    }

                    if (selected)
                        ImGui::SetItemDefaultFocus();
                }

                ImGui::EndCombo();
            }

        }

        ImGui::End();
    }

}
