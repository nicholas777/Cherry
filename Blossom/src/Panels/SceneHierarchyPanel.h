#pragma once

#include "Cherry.h"
#include "Graphics/UI/UIComponent.h"
#include "Graphics/UI/Label.h"
#include "Graphics/UI/Button.h"

namespace Cherry
{
	class SceneObject : public UIElement
	{

	};

	class SceneHierarchyPanel : public UI, public EventListener
	{
	public:
		SceneHierarchyPanel();

		virtual void OnUpdate() override;
		virtual void OnEvent(Event e) override;
	private:
		std::vector<SceneObject*> m_Objects;
	};

}
