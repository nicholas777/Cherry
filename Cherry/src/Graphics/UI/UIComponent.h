#pragma once

#include "core/Core.h"
#include "Math/Vector.h"

namespace Cherry
{
	class UIElement
	{
	public:
		virtual ~UIElement() = default;
		virtual void OnUpdate() = 0;

		bool IsVisible = true;
	};

	class UI
	{
	public:
		UI(Vector2f pos, Vector2f size);
		virtual ~UI() = default;

		virtual void OnUpdate() = 0;

	protected:
		Vector2f m_Position, m_Size;
		
		// TODO: Dont update UI if no changes happen
		bool m_ShouldUpdate = true;
	};
}
