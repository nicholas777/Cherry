#pragma once

#include "core/Core.h"
#include "System/SystemInfo.h"

namespace Cherry
{
	class CHERRY_API WindowsSystemInfoLoader : public SystemInfoLoader
	{
	protected:
		virtual void LoadSystemInfoImpl() override;
	};

#ifdef CH_PLATFORM_WINDOWS
	void SystemInfoLoader::InitSystemInfoLoader()
	{
		m_Instance = new WindowsSystemInfoLoader();
	}
#endif
}
