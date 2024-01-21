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

}

#define CH_INSTRUMENTATION_DIR "assets"

#ifdef CH_DEBUG_MODE
    #define CH_ENABLE_LOGGING 1
    #define CH_ENABLE_ASSERTS 1
    #define CH_ENABLE_PROFILER 1
#endif

#ifdef CH_RELEASE_MODE
    #define CH_EBABLE_LOGGING 1
    #define CH_EBABLE_ASSERTS 0
    #define CH_ENABLE_PROFILER 1
#endif

#ifdef CH_DIST_MODE
    #define CH_ENABLE_LOGGING 0
    #define CH_ENABLE_ASSERTS 0
    #define CH_ENABLE_PROFILER 0
#endif

#if CH_ENABLE_LOGGING == 1
    #define CH_TRACE(...) Cherry::Log::GetClientLogger()->trace(__VA_ARGS__)
    #define CH_INFO(...) Cherry::Log::GetClientLogger()->info(__VA_ARGS__)
    #define CH_WARNING(...) Cherry::Log::GetClientLogger()->warn(__VA_ARGS__)
    #define CH_ERROR(...) Cherry::Log::GetClientLogger()->error(__VA_ARGS__)
    #define CH_FATAL(...) Cherry::Log::GetClientLogger()->critical(__VA_ARGS__)
#else
    #define CH_TRACE(...)
    #define CH_INFO(...)
    #define CH_WARNING(...)
    #define CH_ERROR(...)
    #define CH_FATAL(...)
#endif

#if CH_ENABLE_ASSERTS == 1
    #include <assert.h>

    #define CH_ASSERT(condition, error) { CH_ERROR(error); assert(condition); }
    #define CH_VALIDATE(condition) { assert(condition); }
#else
    #define CH_ASSERT(condition, error)
    #define CH_VALIDATE(condition)
#endif

