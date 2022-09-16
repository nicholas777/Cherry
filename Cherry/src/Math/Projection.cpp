#include "epch.h"
#include "Projection.h"

namespace Cherry
{
	Matrix4x4f ortho(float left, float right, float top, float bottom, float farPlane, float nearPlane)
	{
		return Matrix4x4f(
			Vector4f(2.0f / (right - left), 0, 0, -((right + left) / (right - left))),
			Vector4f(0, 2 / (top - bottom), 0, -((top + bottom) / (top - bottom))),
			Vector4f(0, 0, -2 / (farPlane - nearPlane), -((farPlane + nearPlane) / (farPlane - nearPlane))),
			Vector4f(0, 0, 0, 1)
		);
	}
}
