#pragma once

#include "Matrix.h"
#include "Vector.h"

namespace Cherry
{
	class CHERRY_API TransformationMatrix : public Matrix4x4f
	{
	public:
		TransformationMatrix()
		: m_Translation(0.0f, 0.0f), m_Rotation(0.0f), m_Scale(1.0f, 1.0f) { SetIdentity(); };

		TransformationMatrix(float x, float y);
		TransformationMatrix(const Vector2f& pos);

		void Translate(const Vector2f& translation);
		void Rotate(float rotation);
		void Scale(const Vector2f& scalar);
		void Scale(float scalar);

		void SetTranslation(Vector2f translation);
		void SetRotation(float rotation);
		void SetScale(Vector2f scalar);
		void SetScale(float scalar);

		void operator=(Matrix4x4f mat);
		Vector4f operator*(Vector4f vec);

	private:
		Vector2f m_Translation;
		float m_Rotation;
		Vector2f m_Scale;
	};
}