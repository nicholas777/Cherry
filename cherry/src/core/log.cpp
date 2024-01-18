#include "epch.h"

#include "log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Cherry
{
	std::shared_ptr<spdlog::logger> Log::m_EngineLogger;
	std::shared_ptr<spdlog::logger> Log::m_ClientLogger;
	
	void Log::Init(const std::string& AppName)
	{
		spdlog::set_pattern("%^[%H:%M:%S] [%l] %n: %v´%$");

		m_EngineLogger = spdlog::stdout_color_mt("Cherry");
		m_EngineLogger->set_level(spdlog::level::trace);

		m_ClientLogger = spdlog::stdout_color_mt(AppName);
		m_ClientLogger->set_level(spdlog::level::trace);
	}
}
