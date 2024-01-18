#include "epch.h"
#include "systemInfo.h"
#include "fileDialogs.h"

#include "platform/windows/windowsSystemInfoLoader.h"
#include "platform/windows/windowsFileDialogs.h"

namespace Cherry
{
#ifdef CH_PLATFORM_WINDOWS
	SystemInfoLoader* SystemInfoLoader::m_Instance = new WindowsSystemInfoLoader();
	FileDialogManager* FileDialogManager::m_Instance = new WindowsFileDialogManager();
#endif
}
