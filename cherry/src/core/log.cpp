#include "log.h"

#include "debug/profiler.h"
#include "epch.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Cherry {
    std::shared_ptr<spdlog::logger> Log::m_ClientLogger;

    void Log::Init(const std::string& appName) {
        CH_PROFILE_FUNC();

        spdlog::set_pattern("%^[%H:%M:%S] [%l] %n: %v´%$");

        m_ClientLogger = spdlog::stdout_color_mt(appName);
        m_ClientLogger->set_level(spdlog::level::trace);
    }
}
