#include "PropertiesPanel.h"
#include "EditorLayer.h"

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
            m_UseTexture = m_Current.GetComponent<SpriteComponent>().UseTexture;
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
        CH_PROFILE_FUNC();

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
            bool removeComponent = false;

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow;
            bool opened = ImGui::TreeNodeEx((void*)0, flags, "Name Component");

            if (ImGui::BeginPopupContextItem("Name Component"))
            {
                ImGui::BeginDisabled();
                if (ImGui::MenuItem("Remove Component"))
                {
                    removeComponent = true;
                }
                ImGui::EndDisabled();
                ImGui::EndPopup();
            }

            if (opened)
            {
                char str[128];
                memset(str, 0, sizeof(str));
                strcpy(str, name.Name.c_str());
                
                if (ImGui::InputText("Name", str, sizeof(str), ImGuiInputTextFlags_EnterReturnsTrue))
                {
                    auto action = new NameComponentEditAction();
                    action->entity = m_Current;

                    action->oldName = name.Name;
                    action->newName = str;

                    EditorLayer::RegisterAction(action);
                    name.Name = str;
                }

                ImGui::TreePop();
            }

            if (removeComponent)
            {
                m_Current.RemoveComponent<NameComponent>();
            }

        }

        if (m_Current.HasComponent<TransformComponent>())
        {
            bool removeComponent = false;

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow;
            bool opened = ImGui::TreeNodeEx((void*)1, flags, "Transform");

            if (ImGui::BeginPopupContextItem("Transform Component"))
            {
                if (ImGui::MenuItem("Remove Component"))
                {
                    removeComponent = true;
                }

                ImGui::EndPopup();
            }

            if (opened)
            {
                TransformComponent& transform = m_Current.GetComponent<TransformComponent>();

                float translation[2] = {
                    transform.Translation.x,
                    transform.Translation.y
                };

                if (ImGui::InputFloat2("Translation", translation, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
                {
                    auto action = new TransformComponentEditAction();
                    action->entity = m_Current;

                    action->oldPos = transform.Translation;
                    action->newPos = translation;

                    action->oldRot = transform.Rotation;
                    action->newRot = transform.Rotation;

                    action->oldSize = transform.Scale;
                    action->newSize = transform.Scale;

                    EditorLayer::RegisterAction(action);
                    transform.Translation = translation;
                }
                // TODO: Rotation is broken
                float rotation = transform.Rotation;
                if (ImGui::InputFloat("Rotation", &rotation, ImGuiInputTextFlags_EnterReturnsTrue))
                {
                    auto action = new TransformComponentEditAction();
                    action->entity = m_Current;

                    action->oldPos = transform.Translation;
                    action->newPos = transform.Translation;

                    action->oldRot = transform.Rotation;
                    action->newRot = rotation;

                    action->oldSize = transform.Scale;
                    action->newSize = transform.Scale;

                    EditorLayer::RegisterAction(action);
                    transform.Rotation = rotation;
                }

                float scale[2] = {
                    transform.Scale.x,
                    transform.Scale.y
                };

                if (ImGui::InputFloat2("Scale", scale, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
                {
                    auto action = new TransformComponentEditAction();
                    action->entity = m_Current;

                    action->oldPos = transform.Translation;
                    action->newPos = transform.Translation;

                    action->oldRot = transform.Rotation;
                    action->newRot = transform.Rotation;

                    action->oldSize = transform.Scale;
                    action->newSize = scale;

                    EditorLayer::RegisterAction(action);
                    transform.Scale = scale;
                }

                ImGui::TreePop();
            }

            if (removeComponent)
            {
                m_Current.RemoveComponent<TransformComponent>();
            }

        }

        if (m_Current.HasComponent<SpriteComponent>())
        {
            bool removeComponent = false;

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow;
            bool opened = ImGui::TreeNodeEx((void*)2, flags, "Sprite Component");

            if (ImGui::BeginPopupContextItem("Sprite Component"))
            {
                if (ImGui::MenuItem("Remove Component"))
                {
                    removeComponent = true;
                }

                ImGui::EndPopup();
            }

            if (opened)
            {
                SpriteComponent& sprite = m_Current.GetComponent<SpriteComponent>();
                
                int useTexture;
                if (ImGui::RadioButton("Use color", &useTexture, 0))
                {
                    auto action = new SpriteComponentEditAction();
                    action->entity = m_Current;

                    action->oldUseTexture = sprite.UseTexture;
                    action->newUseTexture = useTexture != 0;

                    action->oldColor = sprite.Color;
                    action->newColor = sprite.Color;

                    action->oldTexture = *sprite.SpriteTexture;
                    action->newTexture = *sprite.SpriteTexture;

                    EditorLayer::RegisterAction(action);

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

                    auto action = new SpriteComponentEditAction();
                    action->entity = m_Current;

                    action->oldUseTexture = sprite.UseTexture;
                    action->newUseTexture = useTexture != 0;

                    action->oldColor = sprite.Color;
                    action->newColor = sprite.Color;

                    action->oldTexture = *sprite.SpriteTexture;
                    action->newTexture = *sprite.SpriteTexture;

                    EditorLayer::RegisterAction(action);

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

                    if (ImGui::ColorEdit4("Color", buffer, ImGuiInputTextFlags_EnterReturnsTrue))
                    {
                        sprite.Color = buffer;
                    }
                }
                else
                {
                    if (!sprite.SpriteTexture->texture.IsAlive())
                    {
                        ImGui::Text("This entity doesn't have a texture attached");
                        if (ImGui::BeginDragDropTarget())
                        {
                            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("AssetTexture"))
                            {
                                CH_ASSERT(payload->DataSize == sizeof(uint32_t), "");

                                auto action = new SpriteComponentEditAction();
                                action->entity = m_Current;

                                action->oldUseTexture = sprite.UseTexture;
                                action->newUseTexture = sprite.UseTexture;

                                action->oldColor = sprite.Color;
                                action->newColor = sprite.Color;

                                action->oldTexture = *sprite.SpriteTexture;

                                sprite.SpriteTexture = new SubTexture(
                                    AssetManager::GetTexture((*(const uint32_t*)payload->Data)).ptr
                                );

                                action->newTexture = *sprite.SpriteTexture;

                                EditorLayer::RegisterAction(action);

                            }

                            ImGui::EndDragDropTarget();
                        }

                    }
                    else
                    {
                        ImGui::Text("Texture");
                        ImGui::Image(
                            (void*)sprite.SpriteTexture->texture->GetTextureID(), 
                            ImVec2(160.0f, 160.0f), ImVec2(0, 1), 
                            ImVec2(1, 0));

                        if (ImGui::BeginDragDropTarget())
                        {
                            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("AssetTexture"))
                            {
                                CH_ASSERT(payload->DataSize == sizeof(uint32_t), "");
                                
                                auto action = new SpriteComponentEditAction();
                                action->entity = m_Current;

                                action->oldUseTexture = sprite.UseTexture;
                                action->newUseTexture = sprite.UseTexture;

                                action->oldColor = sprite.Color;
                                action->newColor = sprite.Color;

                                action->oldTexture = *sprite.SpriteTexture;

                                sprite.SpriteTexture = new SubTexture(
                                    AssetManager::GetTexture((*(const uint32_t*)payload->Data)).ptr,
                                    sprite.SpriteTexture->textureCoords[0],
                                    sprite.SpriteTexture->textureCoords[2]
                                );

                                action->newTexture = *sprite.SpriteTexture;

                                EditorLayer::RegisterAction(action);
                                
                            }

                            ImGui::EndDragDropTarget();
                        }

                        float bl[2] =
                        {
                            sprite.SpriteTexture->textureCoords[0].x,
                            sprite.SpriteTexture->textureCoords[0].y
                        };

                        float tr[2] =
                        {
                            sprite.SpriteTexture->textureCoords[2].x,
                            sprite.SpriteTexture->textureCoords[3].y
                        };

                        if (ImGui::InputFloat2("Bottom-Left UV", bl))
                        {
                            auto action = new SpriteComponentEditAction();
                            action->entity = m_Current;

                            action->oldUseTexture = sprite.UseTexture;
                            action->newUseTexture = sprite.UseTexture;

                            action->oldColor = sprite.Color;
                            action->newColor = sprite.Color;

                            action->oldTexture = *sprite.SpriteTexture;
                            sprite.SpriteTexture->textureCoords[0] = bl;
                            sprite.SpriteTexture->textureCoords[1] = Vector2f(tr[0], bl[1]);
                            sprite.SpriteTexture->textureCoords[3] = Vector2f(bl[0], tr[1]);
                            action->newTexture = *sprite.SpriteTexture;

                            EditorLayer::RegisterAction(action);
                        }

                        if (ImGui::InputFloat2("Top-Right UV", tr))
                        {
                            auto action = new SpriteComponentEditAction();
                            action->entity = m_Current;

                            action->oldUseTexture = sprite.UseTexture;
                            action->newUseTexture = sprite.UseTexture;

                            action->oldColor = sprite.Color;
                            action->newColor = sprite.Color;

                            action->oldTexture = *sprite.SpriteTexture;
                            sprite.SpriteTexture->textureCoords[1] = Vector2f(tr[0], bl[1]);
                            sprite.SpriteTexture->textureCoords[2] = tr;
                            sprite.SpriteTexture->textureCoords[3] = Vector2f(bl[0], tr[1]);
                            action->newTexture = *sprite.SpriteTexture;

                            EditorLayer::RegisterAction(action);
                        }
                    }
                }

                ImGui::TreePop();
            }

            if (removeComponent)
            {
                m_Current.RemoveComponent<SpriteComponent>();
            }
        }

        if (m_Current.HasComponent<CameraComponent>())
        {
            bool removeComponent = false;

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow;
            bool opened = ImGui::TreeNodeEx((void*)3, flags, "Camera Component");

            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("Remove Component"))
                {
                    removeComponent = true;
                }

                ImGui::EndPopup();
            }

            if (opened)
            {
                CameraComponent& comp = m_Current.GetComponent<CameraComponent>();

                if (ImGui::Checkbox("Primary", &comp.IsPrimary))
                {
                    auto action = new CameraComponentEditAction();
                    action->entity = m_Current;

                    action->oldPrimary = !comp.IsPrimary;
                    action->newPrimary = comp.IsPrimary;

                    action->oldCamera = comp.camera;
                    action->newCamera = comp.camera;

                    EditorLayer::RegisterAction(action);
                }

                float span = comp.camera.GetSpan();
                if (ImGui::InputFloat("Span", &span, ImGuiInputTextFlags_EnterReturnsTrue))
                {
                    auto action = new CameraComponentEditAction();
                    action->entity = m_Current;

                    action->oldPrimary = comp.IsPrimary;
                    action->newPrimary = comp.IsPrimary;

                    action->oldCamera = comp.camera;
                    comp.camera.SetSpan(span);
                    comp.camera.RecelcProjection();
                    action->newCamera = comp.camera;

                    EditorLayer::RegisterAction(action);
                }

                float znear = comp.camera.GetNear();
                if (ImGui::InputFloat("Near plane", &znear, ImGuiInputTextFlags_EnterReturnsTrue))
                {
                    auto action = new CameraComponentEditAction();
                    action->entity = m_Current;

                    action->oldPrimary = comp.IsPrimary;
                    action->newPrimary = comp.IsPrimary;

                    action->oldCamera = comp.camera;
                    comp.camera.SetNear(znear);
                    comp.camera.RecelcProjection();
                    action->newCamera = comp.camera;

                    EditorLayer::RegisterAction(action);
                }

                float zfar = comp.camera.GetFar();
                if (ImGui::InputFloat("Far plane", &zfar, ImGuiInputTextFlags_EnterReturnsTrue))
                {
                    auto action = new CameraComponentEditAction();
                    action->entity = m_Current;

                    action->oldPrimary = comp.IsPrimary;
                    action->newPrimary = comp.IsPrimary;

                    action->oldCamera = comp.camera;
                    comp.camera.SetFar(zfar);
                    comp.camera.RecelcProjection();
                    action->newCamera = comp.camera;

                    EditorLayer::RegisterAction(action);
                }

                ImGui::TreePop();
            }

            if (removeComponent)
            {
                m_Current.RemoveComponent<CameraComponent>();
            }
        }

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow;
        if (ImGui::TreeNodeEx((void*)5, flags, "Component Browser"))
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
                        m_Current.AddComponent<SpriteComponent>().SpriteTexture = new SubTexture(Shared<Texture>(nullptr));
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
        CH_PROFILE_FUNC();

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
