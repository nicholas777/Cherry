#include "epch.h"
#include "CameraController.h"

namespace Cherry
{
	CameraController::CameraController(Camera* cam, float force)
		: m_Camera(cam), m_Force(force),
		EventListener({ EventType::MouseScrollEvent })
	{
	}

	void CameraController::Update(float delta)
	{
		float x = 0, y = 0;

		if (Input::GetKeyPressed(Key::W))
		{
			y += m_Force;
		}
		if (Input::GetKeyPressed(Key::S))
		{
			y -= m_Force;
		}
		if (Input::GetKeyPressed(Key::A))
		{
			x -= m_Force;
		}
		if (Input::GetKeyPressed(Key::D))
		{
			x += m_Force;
		}
		
		if (!(x == 0 && y == 0))
		{
			//m_Camera->Translate(-(x * delta), -(y * delta));
		}
		
	}

	void CameraController::OnEvent(Event& e)
	{
		MouseScrollEvent& event = static_cast<MouseScrollEvent&>(e);

		//m_Camera->Zoom(event.Offset);
	}
}