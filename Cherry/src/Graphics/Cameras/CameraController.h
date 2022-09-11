#pragma once

#include "core/Core.h"
#include "Camera.h"
#include "Events/Input.h"

namespace Cherry
{
	class CameraController
	{
	public:
		CameraController() = default;
		CameraController(Camera* cam, float force);

		void Update(float delta);
	private:
		Camera* m_Camera;
		float m_Force;
	};
}
