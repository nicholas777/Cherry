#pragma once

#include "Cherry.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/PropertiesPanel.h"

namespace Cherry
{
	class EditorLayer : public Layer
	{
	public:

		virtual ~EditorLayer() override;

		virtual void OnAttach() override;
		virtual void OnUpdate(const Timestep& delta) override;

		virtual void OnImGuiRender() override;

		static void SelectEntity(const Entity& entity);

	private:
		Scoped<Texture> m_SmileTexture;

		Shared<Font> m_Font;

		static Scoped<SceneHierarchyPanel> m_SceneHierarchyPanel;
		static Scoped<PropertiesPanel> m_PropertiesPanel;

		Shared<Scene> m_Scene;

		Scoped<Framebuffer> m_Framebuffer;

		Vector2f m_ViewportPanelSize;

		Entity m_EditorCamera;
	};
}