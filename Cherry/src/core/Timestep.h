#pragma once

#include "core/Core.h"

namespace Cherry
{
	struct CHERRY_API Timestep
	{
		Timestep()
			: m_Time(0.0f)
		{
		}

		Timestep(float time)
			: m_Time(time)
		{
		}

		float GetSeconds() { return m_Time; }
		float GetMilliseconds() { return m_Time * 1000; }

	private:
		float m_Time;
	};
}