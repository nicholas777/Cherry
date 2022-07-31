#pragma once

#include <vector>
#include "EventListener.h"
#include "core/KeyCodes.h"
#include "core/MouseButtonCodes.h"
#include "Math/Vector.h"

namespace Cherry
{

	class CHERRY_API Input
	{
		
	public:

		static bool GetKeyPressed(Key keycode) 
		{ 
			return m_Instance->GetKeyPressedImpl(keycode); 
		};

		static bool GetMousePressed(MouseButton mousecode) 
		{ 
			return m_Instance->GetMousePressedImpl(mousecode); 
		};
		
		static Vector2f GetMousePos() 
		{
			return m_Instance->GetMousePosImpl();
		};

		static float GetMouseX()
		{
			return m_Instance->GetMouseXImpl();
		};

		static float GetMouseY() 
		{
			return m_Instance->GetMouseYImpl();
		};

		static void Init();

	protected:

		virtual bool GetKeyPressedImpl(Key keycode) { return false; };
		virtual bool GetMousePressedImpl(MouseButton mousecode) { return false; };

		virtual Vector2f GetMousePosImpl() { return Vector2f(); };
		virtual float GetMouseXImpl() { return 0.0; };
		virtual float GetMouseYImpl() { return 0.0; };

		static Input* m_Instance;
	};

}
