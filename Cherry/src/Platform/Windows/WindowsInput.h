#include "epch.h"
#include <vector>
#include <GLFW/glfw3.h>

#include "Events/Input.h"
#include "core/Application.h"
#include "core/KeyCodes.h"
#include "core/MouseButtonCodes.h"

namespace Cherry
{
	class CHERRY_API WindowsInput : public Input
	{
	protected:

		GLFWwindow* window;

		virtual bool GetKeyPressedImpl(Key keycode) override
		{
			return glfwGetKey(window, static_cast<int32_t>(keycode)) == GLFW_PRESS;
		};

		virtual bool GetMousePressedImpl(MouseButton mousecode) override
		{ 
			return glfwGetMouseButton(window, static_cast<int32_t>(mousecode)) == GLFW_PRESS;
		};

		virtual std::vector<float> GetMousePosImpl() override
		{ 
			double x, y;
			glfwGetCursorPos(window, &x, &y);
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
		WindowsInput* Initialize()
		{
			window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow()->GetNativeWindow());
			return this;
		}

		friend void Cherry::Input::Init();
	};

#ifdef CH_PLATFORM_WINDOWS
	void Cherry::Input::Init()
	{
		m_Instance = (new WindowsInput())->Initialize();
	}
#endif
}