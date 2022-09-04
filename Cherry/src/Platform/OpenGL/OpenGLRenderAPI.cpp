#include "epch.h"
#include "OpenGLRenderAPI.h"

#include <glad/glad.h>

namespace Cherry
{
	void OpenGLRenderAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRenderAPI::SetViewport(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRenderAPI::SetClearColor(Vector4f color)
	{
		glClearColor(color.x, color.y, color.z, color.w);
	}

	void OpenGLRenderAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderAPI::DrawElements(VertexArray* vao, uint32_t indexCount)
	{
		uint32_t indices = indexCount != -1 ? indexCount : vao->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, nullptr);
	}
}
