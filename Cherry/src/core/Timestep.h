#pragma once

#include "core/Core.h"
#include "core/Log.h"

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

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000; }

	private:
		float m_Time;
	};
}