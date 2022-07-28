#include "epch.h"
#include "OpenGLRenderAPI.h"

#include <glad/glad.h>

namespace Cherry
{
	void OpenGLRenderAPI::SetClearColor(Vector4f color)
	{
		glClearColor(color.x, color.y, color.z, color.w);
	}

	void OpenGLRenderAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderAPI::DrawElements(VertexArray* vao)
	{
		vao->Bind();
		glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}