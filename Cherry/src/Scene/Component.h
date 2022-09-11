#pragma once

#include "core/Core.h"
#include "Math/Matrix.h"
#include "core/Pointer.h"
#include "Renderer/Texture.h"

namespace Cherry
{
	struct NameComponent
	{
		std::string Name;

		NameComponent() = default;
		NameComponent(const NameComponent&) = default;

		NameComponent(const std::string& name)
			: Name(name) {}
	};

	struct TransformComponent
	{
		Vector2f Translation = Vector2f(0.0f);
		float Rotation = 0.0f;
		Vector2f Scale = Vector2f(1.0f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const Vector2f& pos, float rot, const Vector2f scale)
			: Translation(pos), Rotation(rot), Scale(scale) {}

		Matrix4x4f GetMatrix()
		{
			Matrix4x4f mat = Matrix4x4f::Identity();

			Translate(&mat, Translation.x, Translation.y);
			Rotate(&mat, Rotation);
			Cherry::Scale(&mat, Scale.x, Scale.y);

			return mat;
		}
	};

	struct SpriteComponent
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
