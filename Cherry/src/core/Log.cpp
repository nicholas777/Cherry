#include "epch.h"
#include "Log.h"

namespace Cherry
{
	std::shared_ptr<spdlog::logger> Log::m_EngineLogger;
	std::shared_ptr<spdlog::logger> Log::m_ClientLogger;
	
	void Log::Init()
	{
		spdlog::set_pattern("%^[%H:%M:%S] [%l] %n: %v´%$");

		m_EngineLogger = spdlog::stdout_color_mt("Cherry");
		m_EngineLogger->set_level(spdlog::level::trace);

		m_ClientLogger = spdlog::stdout_color_mt("App");
		m_ClientLogger->set_level(spdlog::level::trace);
	}
}