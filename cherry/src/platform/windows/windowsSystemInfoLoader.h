#pragma once

#include "system/systemInfo.h"

namespace Cherry
{
	class WindowsSystemInfoLoader : public SystemInfoLoader
	{
	protected:
		virtual void LoadSystemInfoImpl() override;
	};
}
