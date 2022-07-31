#pragma once

#include "Renderer/RenderAPI.h"
#include <glad/glad.h>

namespace Cherry
{
	class CHERRY_API OpenGLRenderAPI : public RenderAPI
	{
	public:
		virtual void Init() override;

		virtual void SetViewport(int x, int y, int width, int height) override;

		virtual void SetClearColor(Vector4f color) override;
		virtual void Clear() override;

		virtual void DrawElements(VertexArray* vao) override;
	};
}
