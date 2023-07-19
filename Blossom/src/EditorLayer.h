#pragma once

#include "Cherry.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/PropertiesPanel.h"
#include "Panels/ContentBrowserPanel.h"
#include "EditorAction.h"

#include <filesystem>

namespace Cherry
{
	enum class EditorState
	{
		None = 0,
		Edit,
		Runtime
	};

	class EditorLayer : public Layer
	{
	public:
		EditorLayer()
			: Layer("EditorLayer") {};
		virtual ~EditorLayer() override {};

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(const Timestep& delta) override;

		virtual void OnEvent(Event& e) override;

		virtual void OnImGuiRender() override;

		static void SelectEntity(const Entity& entity);
		static void SelectAsset(Asset* asset);
		static void SelectScene(Scene* asset, std::string path);
		static void ToggleRuntime();

		static void RegisterAction(ReversableAction* action);
		static void UndoAction();
		static void RedoAction();

	private:

		static std::vector<ReversableAction*> m_ActionsToUndo;
		static std::vector<ReversableAction*> m_ActionsToRedo;

		static Scoped<SceneHierarchyPanel> m_SceneHierarchyPanel;
		static Scoped<PropertiesPanel> m_PropertiesPanel;
		static Scoped<ContentBrowserPanel> m_ContentBrowserPanel;

		static std::string m_ProjectPath;

		static Scene* m_Scene;
		static Scene* m_RuntimeScene;
		static std::string m_ScenePath;
		static EditorState m_State;

		Scoped<Framebuffer> m_Framebuffer;
		bool m_EditorChanged = true;

		Vector2f m_ViewportPanelSize;
		Vector2f m_ViewportPanelPos;

		bool m_EntitySelected = false;
		static bool m_IsRuntime;
		StaticCamera m_EditorCamera;
		Shared<Texture> m_PlayButton, m_PauseButton;

		static Entity m_SelectedEntity;

		Shared<Texture> m_RedArrow, m_GreenArrow;
		Vector2i m_GizmoStart, m_GizmoOffset;
		bool m_GizmoSelected = false;
		int m_GizmoType = 0;
		Vector2f m_GizmosPrevTranslation;

		void OpenFile();
		void SaveFile();
		void SaveFileAs();

		void ReloadAssets();
	};
}