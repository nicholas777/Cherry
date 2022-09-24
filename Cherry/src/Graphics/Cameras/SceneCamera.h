#pragma once

#include "core/Application.h"
#include "Graphics/Cameras/Camera.h"
#include "Math/Projection.h"

namespace Cherry
{
	class SceneCamera : public Camera
	{
	public:
		SceneCamera()
			: m_Span(10.0f), m_Near(-1.0f), m_Far(1.0f)
		{
			float aspect = WINDOW_WIDTH / WINDOW_HEIGHT;
			m_Projection = ortho(-m_Span * aspect, m_Span * aspect, m_Span, -m_Span, m_Far, m_Near);
		}
		
		SceneCamera(float span, float znear, float zfar)
			: m_Span(span), m_Near(znear), m_Far(zfar)
		{
			float aspect = WINDOW_WIDTH / WINDOW_HEIGHT;
			m_Projection = ortho(-span * aspect, span * aspect, span, -span, zfar, znear);
		}

		void RecelcProjection(float aspect = WINDOW_WIDTH / WINDOW_HEIGHT)
		{
			m_Projection = ortho(-m_Span * aspect, m_Span * aspect, m_Span, -m_Span, m_Far, m_Near);
		}

		void ResizeViewport(float width, float height)
		{
			float aspect = width / height;
			m_Projection = ortho(-m_Span * aspect, m_Span * aspect, m_Span, -m_Span, m_Far, m_Near);
		}

		float GetSpan() { return m_Span; }
		float GetNear() { return m_Near; }
		float GetFar()  { return m_Far;  }

		void SetSpan(float span) { m_Span = span; };
		void SetNear(float Near) { m_Near = Near; };
		void SetFar(float Far)   { m_Far  = Far;  };

	private:
		float m_Span, m_Near, m_Far;
	};
}
