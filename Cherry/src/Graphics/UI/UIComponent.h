#pragma once

#include "core/Core.h"
#include "Math/Vector.h"

namespace Cherry
{
	class CHERRY_API UIElement
	{
	public:
		virtual ~UIElement() = default;
		virtual void OnUpdate() = 0;

		bool IsVisible = true;
	};

	class CHERRY_API UI
	{
	public:
		UI(Vector4f color, Vector2f pos, Vector2f size);
		virtual ~UI() = default;

		virtual void OnUpdate() = 0;

	protected:
		Vector4f m_Color;
		Vector2f m_Position, m_Size;
		
		// TODO: Dont update UI if no changes happen
		bool m_ShouldUpdate = true;

		// TODO: Find out what CPU Cache is and optimize
	};
}
