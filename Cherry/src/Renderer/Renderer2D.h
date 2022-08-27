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
		static void Shutdown();

		static void Begin(Camera* cam);
		static void End();

		// Rectangle 
		static void DrawRect(const Vector2f& position, const Vector2f& size, const Scoped<Texture>& texture);
		static void DrawRect(const Vector2f& position, const float& rotation, const Vector2f& size, const Scoped<Texture>& texture);

		static void DrawRect(const Vector2f& position, const Vector2f& size, const SubTexture& texture);
		static void DrawRect(const Vector2f& position, const float& rotation, const Vector2f& size, const SubTexture& texture);

	private:
		static void Flush();
		static void NewBatch();
	};
}
