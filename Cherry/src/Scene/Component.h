#pragma once

#include "core/Core.h"
#include "Math/Matrix.h"
#include "core/Pointer.h"
#include "Renderer/Texture.h"

namespace Cherry
{
	struct CHERRY_API TransformComponent
	{
		Matrix4x4f Transform = Matrix4x4f(1.0f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const Matrix4x4f& mat)
			: Transform(mat) {}

		operator Matrix4x4f() const
		{
			return Transform;
		}
	};

	struct CHERRY_API SpriteComponent
	{
		Vector4f Color = { 1, 1, 1, 1 };
		Shared<Texture> SpriteTexture;

		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent&) = default;

		SpriteComponent(const Vector4f& color)
			: Color(color), SpriteTexture(nullptr) {}

		SpriteComponent(const Shared<Texture>& texture)
			: SpriteTexture(texture) {}
	};
}
