#pragma once

#include "core/Core.h"

namespace Cherry
{
	struct SystemInfo
	{

	};

	class SystemInfoLoader
	{
	public:
		static void LoadSystemInfo()
		{
			m_Instance->LoadSystemInfoImpl();
		};

		static SystemInfo GetSystemInfo()
		{
			return SystemInfo();
		};

		static void InitSystemInfoLoader();

	protected:

		virtual void LoadSystemInfoImpl() {};

	private:
		static SystemInfoLoader* m_Instance;
	};
}