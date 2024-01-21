#include "epch.h"

#include "profiler.h"

namespace Cherry
{
	Profiler::InstrumentationSession* Profiler::m_Session = nullptr;
	std::ofstream Profiler::m_Stream;
}
