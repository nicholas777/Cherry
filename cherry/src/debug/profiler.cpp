#include "profiler.h"

#include "epch.h"

namespace Cherry {
    Profiler::InstrumentationSession* Profiler::m_Session = nullptr;
    std::ofstream Profiler::m_Stream;

    void Profiler::BeginSession(const char* name) {
        if (m_Session) {
            EndSession();
        }

        m_Session = new InstrumentationSession;
        m_Session->Name = name;

        m_Stream.open(((std::string(CH_INSTRUMENTATION_DIR) + "/instrumentation_") + name) +
                      ".json");

        m_Stream << "{\"otherData\": {},\"traceEvents\":[{}";
        m_Stream.flush();
    }

    void Profiler::EndSession() {
        if (!m_Session)
            return;

        m_Stream << "]}";
        m_Stream.flush();
        m_Stream.close();

        delete m_Session;
        m_Session = nullptr;
    }

    void Profiler::WriteInstrumentationData(const char* name, long long start, long long end) {
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
}
