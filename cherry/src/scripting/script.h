#pragma once

#include "core/pointer.h"
#include "class.h"

namespace Cherry
{

    class MonoAssembly;
    class MonoDomain;
    class MonoImage;
    class MonoTableInfo;
	
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
