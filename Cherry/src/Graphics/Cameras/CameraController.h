#pragma once

#include "core/Core.h"
#include "Camera.h"
#include "Events/Input.h"
#include "Events/EventListener.h"

namespace Cherry
{
	class CameraController : public EventListener
	{
	public:
		CameraController()
			: EventListener({ EventType::MouseScrollEvent }) {};
		CameraController(Camera* cam, float force);

		void Update(float delta);
		virtual void OnEvent(Event& e) override;
	private:
		Camera* m_Camera;
		float m_Force;
	};
}
