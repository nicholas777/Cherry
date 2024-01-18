#pragma once

#include "spdlog/spdlog.h"

namespace Cherry
{
    class Log
    {
    public:
        static void Init(const std::string& AppName);
        inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return m_EngineLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> m_EngineLogger;
        static std::shared_ptr<spdlog::logger> m_ClientLogger;
    };

#ifdef CH_DEBUG_MODE
	#define CH_TRACE(...) Cherry::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define CH_INFO(...) Cherry::Log::GetClientLogger()->info(__VA_ARGS__)
	#define CH_WARNING(...) Cherry::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define CH_ERROR(...) Cherry::Log::GetClientLogger()->error(__VA_ARGS__)
	#define CH_FATAL(...) Cherry::Log::GetClientLogger()->fatal(__VA_ARGS__)
	                   
	#define CH_CORE_TRACE(...) Cherry::Log::GetEngineLogger()->trace(__VA_ARGS__)
	#define CH_CORE_INFO(...) Cherry::Log::GetEngineLogger()->info(__VA_ARGS__)
	#define CH_CORE_WARNING(...) Cherry::Log::GetEngineLogger()->warn(__VA_ARGS__)
	#define CH_CORE_ERROR(...) Cherry::Log::GetEngineLogger()->error(__VA_ARGS__)
	#define CH_CORE_FATAL(...) Cherry::Log::GetEngineLogger()->fatal(__VA_ARGS__)
#endif

#ifdef CH_RELEASE_MODE
	#define CH_TRACE(...) Cherry::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define CH_INFO(...) Cherry::Log::GetClientLogger()->info(__VA_ARGS__)
	#define CH_WARNING(...) Cherry::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define CH_ERROR(...) Cherry::Log::GetClientLogger()->error(__VA_ARGS__)
	#define CH_FATAL(...) Cherry::Log::GetClientLogger()->fatal(__VA_ARGS__)

	#define CH_CORE_TRACE(...) Cherry::Log::GetEngineLogger()->trace(__VA_ARGS__)
	#define CH_CORE_INFO(...) Cherry::Log::GetEngineLogger()->info(__VA_ARGS__)
	#define CH_CORE_WARNING(...) Cherry::Log::GetEngineLogger()->warn(__VA_ARGS__)
	#define CH_CORE_ERROR(...) Cherry::Log::GetEngineLogger()->error(__VA_ARGS__)
	#define CH_CORE_FATAL(...) Cherry::Log::GetEngineLogger()->fatal(__VA_ARGS__)
#endif

#ifdef CH_DIST_MODE
	#define CH_TRACE(...)
	#define CH_INFO(...)
	#define CH_WARNING(...)
	#define CH_ERROR(...)
	#define CH_FATAL(...)

	#define CH_CORE_TRACE(...)
	#define CH_CORE_INFO(...)
	#define CH_CORE_WARNING(...)
	#define CH_CORE_ERROR(...)
	#define CH_CORE_FATAL(...)

#endif

}
