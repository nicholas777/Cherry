#pragma once

#include "system/fileDialogs.h"

namespace Cherry {
    class LinuxFileDialogManager : public FileDialogManager
    {
    public:
        LinuxFileDialogManager() = default;

    protected:
        virtual const char* OpenFileImpl(const char* filter) override;
        virtual const char* SaveFileImpl(const char* filter) override;
    };
}
