#include "SceneHierarchyPanel.h"
#include "core/MouseButtonCodes.h"
#include "EditorLayer.h"
#include "core/Log.h"

#include <math.h>

namespace Cherry
{
    SceneHierarchyPanel::SceneHierarchyPanel(Shared<Scene> scene)
        : m_Scene(scene)
    {

        Entity e1 = m_Scene->CreateEntity("Entity1");
        Entity e2 = m_Scene->CreateEntity("Entity2");
        Entity e3 = m_Scene->CreateEntity("Entity3");
        Entity e4 = m_Scene->CreateEntity("Entity4");
        Entity e5 = m_Scene->CreateEntity("Entity5");
        Entity e6 = m_Scene->CreateEntity("Entity6");
        Entity e7 = m_Scene->CreateEntity("Entity7");
        Entity e8 = m_Scene->CreateEntity("Entity8");
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
        ImGui::Begin("Scene Hierarchy");

        m_Scene->m_Registry.each([&](auto EntityID)
        {
            Entity entity = Entity(EntityID, m_Scene.Get());

            auto& name = entity.GetComponent<NameComponent>();

            ImGuiTreeNodeFlags flags = (m_SelectedEntity == entity ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
            bool opened = ImGui::TreeNodeEx((void*)(uint32_t)entity, flags, name.Name.c_str());

            if (ImGui::IsItemClicked())
            {
                EditorLayer::SelectEntity(entity);
                m_SelectedEntity = entity;
            }

            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("Delete Entity"))
                {
                    m_Scene->DeleteEntity(entity);
                }

                ImGui::EndPopup();
            }

            if (opened)
                ImGui::TreePop();
        });
        
        if (ImGui::BeginPopupContextWindow("A", ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight))
        {
            if (ImGui::MenuItem("Create Entity"))
            {
                m_Scene->CreateEntity("Entity");
            }

            ImGui::EndPopup();
        }

        ImGui::End();
    }
}
