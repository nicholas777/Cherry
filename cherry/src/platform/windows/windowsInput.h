#include <vector>
#include <GLFW/glfw3.h>

#include "events/input.h"
#include "core/application.h"
#include "core/keyCodes.h"
#include "core/mouseButtonCodes.h"
#include "math/vector.h"

namespace Cherry
{
	class WindowsInput : public Input
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

		// TODO: Make this function return screen space coords and have separate convertion function
		virtual Vector2f GetMousePosImpl() override
		{ 
			double x, y;
			glfwGetCursorPos(m_Window, &x, &y);

			return { (float)x / WINDOW_WIDTH * 2 - 1, -((float)y / WINDOW_HEIGHT * 2 - 1) };
		};

		virtual Vector2i GetMousePosRawImpl() override
		{
			double x, y;
			glfwGetCursorPos(m_Window, &x, &y);

			return Vector2i((int)x, (int)y);
		}

		virtual float GetMouseXImpl() override
		{ 
			return GetMousePosImpl()[0];
		};

		virtual float GetMouseYImpl() override
		{ 
			return GetMousePosImpl()[1];
		};

		virtual bool GetMouseDownImpl(MouseButton button)
		{
			return glfwGetMouseButton(m_Window, (int)button) == GLFW_PRESS;
		}

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
