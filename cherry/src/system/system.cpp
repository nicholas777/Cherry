#include "epch.h"
#include "systemInfo.h"
#include "fileDialogs.h"

#ifdef CH_PLATFORM_LINUX
#include "platform/linux/linuxSystemInfoLoader.h"
#include "platform/linux/linuxFileDialogs.h"
#endif

#ifdef CH_PLATFORM_WINDOWS
#include "platform/windows/windowsSystemInfoLoader.h"
#include "platform/windows/windowsFileDialogs.h"
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
