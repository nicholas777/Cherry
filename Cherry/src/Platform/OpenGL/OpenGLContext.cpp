#include "epch.h"
#include "OpenGLContext.h"
#include "core/Log.h"
#include "core/Core.h"

namespace Cherry
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_Window(window)
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CH_ASSERT(success, "failed to load GLAD");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}