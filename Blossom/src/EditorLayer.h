#pragma once

#include "Cherry.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/PropertiesPanel.h"
#include "Panels/ContentBrowserPanel.h"

namespace Cherry
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer()
			: Layer("EditorLayer") {};
		virtual ~EditorLayer() override;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(const Timestep& delta) override;

		virtual void OnEvent(Event& e) override;

		virtual void OnImGuiRender() override;

		static void SelectEntity(const Entity& entity);
		static void SelectAsset(Asset* asset);

	private:

		static Scoped<SceneHierarchyPanel> m_SceneHierarchyPanel;
		static Scoped<PropertiesPanel> m_PropertiesPanel;
		static Scoped<ContentBrowserPanel> m_ContentBrowserPanel;

		Shared<Scene> m_Scene;
		Scoped<Framebuffer> m_Framebuffer;

		Vector2f m_ViewportPanelSize;

		bool m_IsRuntime = false;
		StaticCamera m_EditorCamera;

		static Entity m_SelectedEntity;
	};
}