#pragma once

namespace Cherry {
    class FileDialogManager
    {
    public:
        static std::string OpenFile(const char* filter) { return m_Instance->OpenFileImpl(filter); }

        static std::string SaveFile(const char* filter) { return m_Instance->SaveFileImpl(filter); }

    protected:
        virtual std::string OpenFileImpl(const char* filter) = 0;
        virtual std::string SaveFileImpl(const char* filter) = 0;
    private:
        static FileDialogManager* m_Instance;
    };
}
