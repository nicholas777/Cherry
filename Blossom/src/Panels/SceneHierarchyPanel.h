#pragma once

#include "Cherry.h"

namespace Cherry
{

	class SceneHierarchyPanel : public UI, public EventListener
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(Vector2f pos, Vector2f size, Shared<Font> font, Shared<Scene> scene);
		~SceneHierarchyPanel();

		void SetScene(Shared<Scene> scene);

		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;

	private:
		Vector4f m_Color;
		Shared<Font> m_Font;

		Shared<Scene> m_Scene;

		float m_LineSize;

		// std::vector<SceneObject*> m_Objects;
	};

}
