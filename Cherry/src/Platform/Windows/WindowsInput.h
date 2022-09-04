#include "epch.h"
#include <vector>
#include <GLFW/glfw3.h>

#include "Events/Input.h"
#include "core/Application.h"
#include "core/KeyCodes.h"
#include "core/MouseButtonCodes.h"
#include "Math/Vector.h"

namespace Cherry
{
	class CHERRY_API WindowsInput : public Input
	{
	public:
		WindowsInput()
		{
			m_Window = static_cast<GLFWwindow*>(Application::GetApplication()
				 .GetWindow()
				->GetNativeWindow());
		}
	protected:

		virtual bool GetKeyPressedImpl(Key keycode) override
		{
			return glfwGetKey(m_Window, static_cast<int32_t>(keycode)) == GLFW_PRESS;
		};

		virtual bool GetMousePressedImpl(MouseButton mousecode) override
		{ 
			return glfwGetMouseButton(m_Window, static_cast<int32_t>(mousecode)) == GLFW_PRESS;
		};

		virtual Vector2f GetMousePosImpl() override
		{ 
			double x, y;
			glfwGetCursorPos(m_Window, &x, &y);
			return { (float)x, (float)y };
		};

		virtual float GetMouseXImpl() override
		{ 
			return GetMousePosImpl()[0];
		};

		virtual float GetMouseYImpl() override
		{ 
			return GetMousePosImpl()[1];
		};

	private:

		GLFWwindow* m_Window;

		friend void Cherry::Input::Init();
	};

#ifdef CH_PLATFORM_WINDOWS
	void Cherry::Input::Init()
	{
		m_Instance = new WindowsInput();
	}
#endif
}