#pragma once

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

	protected:

		virtual void LoadSystemInfoImpl() {};

	private:
		static SystemInfoLoader* m_Instance;
	};
}
