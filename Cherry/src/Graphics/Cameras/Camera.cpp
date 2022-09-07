#include "epch.h"
#include "Camera.h"

#include "Events/Input.h"
#include "Math/Algorithm.h"

namespace Cherry
{
	
	Camera::Camera(Vector2f pos, float left, float right, float top, float bottom, float farPlane, float nearPlane)
	{
		if (bottom > top)
		{
			CH_ASSERT(false, "Bottom cannot be larger than top");
			CH_ERROR("Bottom cannot be larger than top");
		}

		m_ProjectionMatrix = Matrix4x4f(
			Vector4f(2.0f / (right - left), 0, 0, -((right + left) / (right - left))),
			Vector4f(0, 2 / (top - bottom), 0, -((top + bottom) / (top - bottom))),
			Vector4f(0, 0, -2 / (farPlane - nearPlane), -((farPlane + nearPlane) / (farPlane - nearPlane))),
			Vector4f(0, 0, 0, 1)
		);

		m_ViewMatrix = TransformationMatrix(pos);

		m_VP = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::Translate(float x, float y)
	{
		m_ViewMatrix.Translate(Vector2f(x, y));
		m_VP = m_ProjectionMatrix * m_ViewMatrix;


	}

	void Camera::Rotate(float angle)
	{
		m_ViewMatrix.Rotate(angle);
		m_VP = m_ProjectionMatrix * m_ViewMatrix;
	}
}
