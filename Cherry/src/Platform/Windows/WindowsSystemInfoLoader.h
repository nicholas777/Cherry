#pragma once

#include "core/Core.h"
#include "System/SystemInfo.h"

namespace Cherry
{
	class WindowsSystemInfoLoader : public SystemInfoLoader
	{
	protected:
		virtual void LoadSystemInfoImpl() override;
	};
}
