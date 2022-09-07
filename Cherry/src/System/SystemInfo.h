#pragma once

#include "core/Core.h"

namespace Cherry
{
	struct CHERRY_API SystemInfo
	{

	};

	class CHERRY_API SystemInfoLoader
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