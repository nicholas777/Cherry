#pragma once

#include "core/keyCodes.h"
#include "core/mouseButtonCodes.h"
#include "math/vector.h"

namespace Cherry
{

	class Input
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

		static Vector2i GetMousePosRaw()
		{
			return m_Instance->GetMousePosRawImpl();
		};

		static float GetMouseX()
		{
			return m_Instance->GetMouseXImpl();
		};

		static float GetMouseY() 
		{
			return m_Instance->GetMouseYImpl();
		};

		static bool GetMouseDown(MouseButton button)
		{
			return m_Instance->GetMouseDownImpl(button);
		}

		static void Init();

	protected:

		virtual bool GetKeyPressedImpl(Key keycode);
		virtual bool GetMousePressedImpl(MouseButton mousecode);

		virtual Vector2f GetMousePosImpl();
		virtual Vector2i GetMousePosRawImpl();

		virtual float GetMouseXImpl();
		virtual float GetMouseYImpl();

		virtual bool GetMouseDownImpl(MouseButton button);

		static Input* m_Instance;
	};

}
