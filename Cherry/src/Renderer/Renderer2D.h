#pragma once

#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "core/Pointer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Graphics/Camera.h"
#include "RenderCommand.h"

namespace Cherry
{
	class CHERRY_API Renderer2D
	{
	public:
		static void Init();

		static void Begin(Camera* cam);
		static void End();

		// Rectangle 
		static void DrawRect(Matrix4x4f* transform, Vector4f color);
		static void DrawRect(Matrix4x4f* transform, const Scoped<Texture*>& color);

	private:

	};
}
