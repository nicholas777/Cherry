#pragma once

#include "Cherry.h"

namespace Cherry
{
	class SceneObject : public UIElement
	{

	};

	class SceneHierarchyPanel : public UI /*, public EventListener*/
	{
	public:
		SceneHierarchyPanel(Shared<Font> font);
		~SceneHierarchyPanel();

		virtual void OnUpdate() override;

		inline static void ButtonClickHandler(const MouseClickEvent& e)
		{
			CH_INFO("Button Clicked!");
		};

	private:
		Scoped<Button> m_Button;
		Vector4f m_Color;

		// std::vector<SceneObject*> m_Objects;
	};

}
