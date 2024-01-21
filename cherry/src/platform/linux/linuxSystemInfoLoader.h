#pragma once

#include "system/systemInfo.h"

namespace Cherry
{
    class LinuxSystemInfoLoader : public SystemInfoLoader
    {
    protected:
        virtual void LoadSystemInfoImpl() override;
    };
}
