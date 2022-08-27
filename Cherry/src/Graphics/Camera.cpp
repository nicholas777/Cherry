#include "epch.h"
#include "Camera.h"

#include "Events/Input.h"
#include "Math/Algorithm.h"

namespace Cherry
{
	
	Camera::Camera(Vector2f pos, float left, float right, float top, float bottom, float farPlane, float nearPlane, Vector3f up)
	{
		m_ProjectionMatrix = Matrix4x4f(
			Vector4f(2.0f / (right - left), 0, 0, -((right + left) / (right - left))),
			Vector4f(0, 2 / (top - bottom), 0, -((top + bottom) / (top - bottom))),
			Vector4f(0, 0, -2 / (farPlane - nearPlane), -((farPlane + nearPlane) / (farPlane - nearPlane))),
			Vector4f(0, 0, 0, 1)
		);

		m_ViewMatrix = TransformationMatrix(pos);

		m_VP = m_ProjectionMatrix * m_ViewMatrix;
	}

	/*void Camera::GenViewMatrix(Vector2f pos, Vector3f up)
	{
		Vector3f f(Algorithm::normalize(Vector3f(pos.x, pos.y, -1) - Vector3f(pos.x, pos.y, 0)));
		Vector3f s(Algorithm::normalize(Algorithm::cross(f, up)));
		Vector3f u(Algorithm::cross(s, f));

		m_ViewMatrix[0][0] = s.x;
		m_ViewMatrix[1][0] = s.y;
		m_ViewMatrix[2][0] = s.z;
		m_ViewMatrix[0][1] = u.x;
		m_ViewMatrix[1][1] = u.y;
		m_ViewMatrix[2][1] = u.z;
		m_ViewMatrix[0][2] = -f.x;
		m_ViewMatrix[1][2] = -f.y;
		m_ViewMatrix[2][2] = -f.z;
		m_ViewMatrix[3][0] = -Algorithm::dot(s, Vector3f(pos));
		m_ViewMatrix[3][1] = -Algorithm::dot(u, Vector3f(pos));
		m_ViewMatrix[3][2] = Algorithm::dot(f, Vector3f(pos));
	}*/

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
