#pragma once

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

namespace Cherry
{
	
	class Script
	{
	public:
		Script()
			: m_Assembly(nullptr), m_Image(nullptr), m_TypeDefinitions(TypeDefinitionsTable()) {};
		Script(MonoAssembly* assembly);
		Script(const std::string& path);
		~Script() { delete m_Assembly; };

		void PrintTypedefs();

	private:

		void LoadTables();

		MonoAssembly* m_Assembly;
		MonoImage* m_Image;

		struct TypeDefinitionsTable
		{
			const MonoTableInfo* Table = nullptr;
			uint32_t Size = 0;

			TypeDefinitionsTable() = default;
		};
		TypeDefinitionsTable m_TypeDefinitions;


	};
}
