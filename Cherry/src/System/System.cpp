#include "epch.h"
#include "SystemInfo.h"
#include "FileDialogs.h"

#include "Platform/Windows/WindowsSystemInfoLoader.h"
#include "Platform/Windows/WindowsFileDialogs.h"

namespace Cherry
{
#ifdef CH_PLATFORM_WINDOWS
	SystemInfoLoader* SystemInfoLoader::m_Instance = new WindowsSystemInfoLoader();
	FileDialogManager* FileDialogManager::m_Instance = new WindowsFileDialogManager();
#endif
}
