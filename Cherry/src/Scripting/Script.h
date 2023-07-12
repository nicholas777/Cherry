#pragma once

#include "core/Pointer.h"
#include "Class.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

namespace Cherry
{
	
	class Assembly
	{
	public:
		Assembly()
			: m_TypeDefinitions(TypeDefinitionsTable()) {};
		Assembly(MonoAssembly* assembly, MonoDomain* appDomain);
		~Assembly();

		void PrintTypedefs();
		Shared<Class> GetClassByName(const char* name, const char* nameSpace = "");

	private:

		void LoadTables();

		MonoAssembly* m_Assembly = nullptr;
		MonoImage* m_Image = nullptr;
		MonoDomain* m_AppDomain = nullptr;

		struct TypeDefinitionsTable
		{
			const MonoTableInfo* Table = nullptr;
			uint32_t Size = 0;

			TypeDefinitionsTable() = default;
			~TypeDefinitionsTable() { };
		};
		TypeDefinitionsTable m_TypeDefinitions;

		friend class ScriptEngine;
	};
}
