#pragma once

#include "Cherry.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/PropertiesPanel.h"
#include "Panels/ContentBrowserPanel.h"
#include <filesystem>
#include "EditorAction.h"

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
		static void SelectScene(Shared<Scene> asset);

		static void RegisterAction(ReversableAction* action);
		static void UndoAction();
		static void RedoAction();

	private:

		static std::vector<ReversableAction*> m_ActionsToUndo;
		static std::vector<ReversableAction*> m_ActionsToRedo;

		static Scoped<SceneHierarchyPanel> m_SceneHierarchyPanel;
		static Scoped<PropertiesPanel> m_PropertiesPanel;
		static Scoped<ContentBrowserPanel> m_ContentBrowserPanel;

		static Shared<Scene> m_Scene;
		std::filesystem::path m_ScenePath;

		Scoped<Framebuffer> m_Framebuffer;
		bool m_EditorChanged = true;

		Vector2f m_ViewportPanelSize;
		Vector2f m_ViewportPanelPos;

		bool m_EntitySelected = false;
		bool m_IsRuntime = false;
		StaticCamera m_EditorCamera;

		static Entity m_SelectedEntity;

		void NewFile();
		void OpenFile();
		void SaveFile();
		void SaveFileAs();
	};
}