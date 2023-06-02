#pragma once

#include "core/Pointer.h"
#include "Script.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

namespace Cherry 
{

	class ScriptEngine
	{
	public:
		static void Init();
		static void Shutdown();

		static Shared<Script> LoadScript(std::string path);

	private:

		static MonoDomain* m_RootDomain;
		static MonoDomain* m_AppDomain;

	};
}