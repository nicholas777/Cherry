#pragma once

namespace Cherry {
    class FileDialogManager
    {
    public:
        static const char* OpenFile(const char* filter) { return m_Instance->OpenFileImpl(filter); }

        static const char* SaveFile(const char* filter) { return m_Instance->SaveFileImpl(filter); }

    protected:
        virtual const char* OpenFileImpl(const char* filter) = 0;
        virtual const char* SaveFileImpl(const char* filter) = 0;
    private:
        static FileDialogManager* m_Instance;
    };
}
