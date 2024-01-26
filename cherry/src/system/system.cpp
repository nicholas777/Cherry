#include "epch.h"
#include "fileDialogs.h"
#include "systemInfo.h"

#ifdef CH_PLATFORM_LINUX
    #include "platform/linux/linuxFileDialogs.h"
    #include "platform/linux/linuxSystemInfoLoader.h"
#endif

#ifdef CH_PLATFORM_WINDOWS
    #include "platform/windows/windowsFileDialogs.h"
    #include "platform/windows/windowsSystemInfoLoader.h"
#endif

namespace Cherry {
#ifdef CH_PLATFORM_WINDOWS
    SystemInfoLoader* SystemInfoLoader::m_Instance = new WindowsSystemInfoLoader();
    FileDialogManager* FileDialogManager::m_Instance = new WindowsFileDialogManager();
#endif

#ifdef CH_PLATFORM_LINUX
    SystemInfoLoader* SystemInfoLoader::m_Instance = new LinuxSystemInfoLoader();
    FileDialogManager* FileDialogManager::m_Instance = new LinuxFileDialogManager();
#endif
}
