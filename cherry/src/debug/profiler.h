#pragma once

#include <chrono>
#include <sstream>

namespace Cherry
{

    class Profiler
    {
    public:
        static void BeginSession(const char* name)
        {
            if (m_Session)
            {
                EndSession();
            }

            m_Session = new InstrumentationSession;
            m_Session->Name = name;

            m_Stream.open(((std::string(CH_INSTRUMENTATION_DIR) + "/instrumentation_") + name) + ".json");

            m_Stream << "{\"otherData\": {},\"traceEvents\":[{}";
            m_Stream.flush();
        }

        static void EndSession()
        {
            if (!m_Session)
                return;

            m_Stream << "]}";
            m_Stream.flush();
            m_Stream.close();

            delete m_Session;
            m_Session = nullptr;
        }

        static void WriteInstrumentationData(const char* name, long long start, long long end)
        {
            m_Stream << ",{";
            m_Stream << "\"cat\":\"function\",";
            m_Stream << "\"dur\":" << (end - start) << ',';
            m_Stream << "\"name\":\"" << name << "\",";
            m_Stream << "\"ph\":\"X\",";
            m_Stream << "\"pid\":0,";
            m_Stream << "\"tid\":0,";
            m_Stream << "\"ts\":" << start;
            m_Stream << "}";

            m_Stream.flush();
        }
    private:
        struct InstrumentationSession
        {
            const char* Name;
        };

        static std::ofstream m_Stream;
        static InstrumentationSession* m_Session;
    };

    class InstrumentationTimer
    {
    public:
        InstrumentationTimer(const char* name)
        {
            m_Name = name;
            m_Start = std::chrono::high_resolution_clock::now();
        }

        ~InstrumentationTimer()
        {
            if (m_Running)
                Stop();
        }

        void Stop()
        {
            m_Running = false;
            auto end = std::chrono::high_resolution_clock::now();


            long long startPoint = std::chrono::time_point_cast<std::chrono::microseconds>(m_Start).time_since_epoch().count();
            long long endPoint = std::chrono::time_point_cast<std::chrono::microseconds>(end).time_since_epoch().count();

            Profiler::WriteInstrumentationData(m_Name, startPoint, endPoint);
        }

    private:
        const char* m_Name;
        bool m_Running = true;
        std::chrono::steady_clock::time_point m_Start;
    };

    #if CH_ENABLE_PROFILER == 1
        #define CH_PROFILE_SCOPE_LINE2(name, line) Cherry::InstrumentationTimer ch_inst_timer##line(name)
        #define CH_PROFILE_SCOPE_LINE(name, line) CH_PROFILE_SCOPE_LINE2(name, line)
        #define CH_PROFILE_SCOPE(name) CH_PROFILE_SCOPE_LINE(name, __LINE__)
        #define CH_PROFILE_FUNC() CH_PROFILE_SCOPE(__FUNCSIG__)
    #else
        #define CH_PROFILE_SCOPE_LINE2(name, line)
        #define CH_PROFILE_SCOPE_LINE(name, line)
        #define CH_PROFILE_SCOPE(name)
        #define CH_PROFILE_FUNC()
    #endif
}
