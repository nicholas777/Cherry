#pragma once

#include "cherry.h"
#include "panels/sceneHierarchyPanel.h"
#include "panels/propertiesPanel.h"
#include "panels/contentBrowserPanel.h"
#include "editorAction.h"

#include <filesystem>

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

		virtual void OnEvent(const Event& e) override;

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

		Shared<Texture> m_RedArrow, m_GreenArrow;
		Vector2i m_GizmoStart, m_GizmoOffset;
		bool m_GizmoSelected = false;
		int m_GizmoType = 0;
		Vector2f m_GizmosPrevTranslation;

		void NewFile();
		void OpenFile();
		void SaveFile();
		void SaveFileAs();
	};
}
