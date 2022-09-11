#pragma once

#include "Math/Matrix.h"
#include "Math/Transform.h"

namespace Cherry
{
	class Camera
	{
	public:
		Camera() {}
		Camera(Vector2f pos, float left, float right, float top, float bottom, float nearPlane, float farPlane);

		void Translate(float x, float y);
		void Rotate(float angle);

		Vector2f GetPosition() { return m_Position; }

		inline Matrix4x4f CalcVP() { return m_VP; };

	private:
		Matrix4x4f m_ProjectionMatrix;
		TransformationMatrix m_ViewMatrix;

		Matrix4x4f m_VP;

		Vector2f m_Position;
	};
}
