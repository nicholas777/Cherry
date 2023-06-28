#include "epch.h"
#include "Log.h"
#include "Debug/Profiler.h"

namespace Cherry
{
	std::shared_ptr<spdlog::logger> Log::m_ClientLogger;
	
	void Log::Init()
	{
		CH_PROFILE_FUNC();

		spdlog::set_pattern("%^[%H:%M:%S] [%l] %n: %v´%$");

		m_ClientLogger = spdlog::stdout_color_mt("App");
		m_ClientLogger->set_level(spdlog::level::trace);
	}
}
