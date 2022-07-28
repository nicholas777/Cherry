#pragma once

#include "Renderer/RenderAPI.h"
#include <glad/glad.h>

namespace Cherry
{
	class CHERRY_API OpenGLRenderAPI : public RenderAPI
	{
	public:
		virtual void SetClearColor(Vector4f color) override;

		virtual void Clear() override;

		virtual void DrawElements(VertexArray* vao) override;
	};
}
