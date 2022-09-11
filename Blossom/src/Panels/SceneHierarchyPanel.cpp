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

        for (uint32_t i = 0; i < m_Scene->m_Registry.size(); i++)
        {
            Entity entity = Entity(m_Scene->m_Registry.data()[i], m_Scene.Get());
            auto& name = m_Scene->m_Registry.get<NameComponent>(m_Scene->m_Registry.data()[i]); 
            
            ImGuiTreeNodeFlags flags = (m_SelectedEntity == entity ? ImGuiTreeNodeFlags_Selected : 0 ) | ImGuiTreeNodeFlags_OpenOnArrow;
            bool opened = ImGui::TreeNodeEx((void*)i, flags, name.Name.c_str());

            if (ImGui::IsItemClicked())
            {
                EditorLayer::SelectEntity(entity);
                m_SelectedEntity = entity;
            }

            if (opened)
                ImGui::TreePop();
        }

        ImGui::End();
    }
}
