#pragma once

#include "epch.h"
#include "core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Cherry
{
	class CHERRY_API Log
	{
	public:
		static void Init(const std::string& AppName);
		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return m_EngineLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> m_EngineLogger;
		static std::shared_ptr<spdlog::logger> m_ClientLogger;
	};
}
