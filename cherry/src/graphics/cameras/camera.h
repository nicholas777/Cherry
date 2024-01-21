#pragma once

#include "math/matrix.h"
#include "math/transform.h"

namespace Cherry
{
	class Camera
	{
	public:
		Camera() = default;
		Camera(const Matrix4x4f& projection)
			: m_Projection(projection) {}

		const Matrix4x4f& GetProjection() const { return m_Projection; }
	protected:
		Matrix4x4f m_Projection;
	};
}
