#pragma once

#include "system/fileDialogs.h"

namespace Cherry
{
    class LinuxFileDialogManager : public FileDialogManager
    {
    public:
        LinuxFileDialogManager() = default;

    protected:
        virtual std::string OpenFileImpl(const char* filter) override;
        virtual std::string SaveFileImpl(const char* filter) override;
    };
}
