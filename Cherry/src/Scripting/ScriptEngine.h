#pragma once

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

namespace Cherry 
{

	class ScriptEngine
	{
	public:
		static void Init();
		static void Shutdown();

		static MonoAssembly* LoadAssembly(std::string path);

	private:
		struct ScriptEngineInfo
		{

		};
		static ScriptEngineInfo m_Info;

		static MonoDomain* m_RootDomain;
		static MonoDomain* m_AppDomain;

	};
}