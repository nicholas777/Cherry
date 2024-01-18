#pragma once

#include "cherry.h"

namespace Cherry
{

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(Shared<Scene> scene);
		~SceneHierarchyPanel();

		void SetScene(Shared<Scene> scene);

		void OnUpdate();

	private:
		Vector4f m_Color;
		Shared<Font> m_Font;

		Shared<Scene> m_Scene;

		Entity m_SelectedEntity = Entity(entt::null, nullptr);

		
	};

}
