#pragma once

#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "core/Pointer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Graphics/Cameras/Camera.h"
#include "RenderCommand.h"

namespace Cherry
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void Begin(const Matrix4x4f& proj, const Matrix4x4f& transform);
		static void Begin();
		static void End();

		// Rectangle 
		static void DrawRect(const Vector2f& position, const Vector2f& size, const Scoped<Texture>& texture);
		static void DrawRect(const Vector2f& position, const Vector2f& size, const SubTexture& texture);
		static void DrawRect(const Vector2f& position, const Vector2f& size, const Vector4f& color);

		static void DrawRect(const Matrix4x4f& transform, const Shared<Texture>& texture, const Vector4f& color = { 1, 1, 1, 1 }, uint32_t entityID = 0);
		static void DrawRect(const Matrix4x4f& transform, const SubTexture& texture, const Vector4f& color = { 1, 1, 1, 1 }, uint32_t entityID = 0);
		static void DrawRect(const Matrix4x4f& transform, const Vector4f& color, uint32_t entityID = 0);

		static void DrawRect(const Vector2f& position, const float& rotation, const Vector2f& size, const Vector4f& color);
		static void DrawRect(const Vector2f& position, const float& rotation, const Vector2f& size, const Scoped<Texture>& texture);
		static void DrawRect(const Vector2f& position, const float& rotation, const Vector2f& size, const SubTexture& texture);

		// Text
		static void DrawChar(const Vector2f& coord1, const Vector2f& coord2, const SubTexture& texture, const Vector4f& color = { 1, 1, 1, 1 });

	private:
		static void Flush();
		static void NewBatch();

		static float GetTextureIndex(Texture* ptr);
	};
}
