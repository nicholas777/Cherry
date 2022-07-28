#pragma once

#include "core/Core.h"
#include "Renderer/RenderingContext.h"
#include <GLFW/glfw3.h>
#include "glad/glad.h"

namespace Cherry
{
	class CHERRY_API OpenGLContext : public RenderingContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_Window;
	};
}