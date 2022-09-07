#pragma once

#include "Cherry.h"
#include "Panels/SceneHierarchyPanel.h"

namespace Cherry
{
	class EditorLayer : public Layer
	{
	public:

		virtual ~EditorLayer() override;

		virtual void OnAttach() override;
		virtual void OnUpdate(const Timestep& delta) override;

	private:
		Scoped<Texture> m_SmileTexture;

		Shared<Font> m_Font;

		Scoped<SceneHierarchyPanel> m_SceneHierarchyPanel;

		Scoped<Scene> m_Scene;

		Scoped<Camera> m_EditorCamera;
		Scoped<Camera> m_LevelEditorCamera;
		Scoped<CameraController> m_LevelEditorCameraController;
	};
}