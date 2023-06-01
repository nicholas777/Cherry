#include "epch.h"
#include "Script.h"
#include "core/Log.h"
#include "ScriptEngine.h"

namespace Cherry
{

	Script::Script(MonoAssembly* assembly)
	{
		m_Assembly = assembly;
		m_Image = mono_assembly_get_image(m_Assembly);

		LoadTables();
	}

	Script::Script(const std::string& path)
	{
		m_Assembly = ScriptEngine::LoadAssembly(path);
		m_Image = mono_assembly_get_image(m_Assembly);

		LoadTables();
	}

	void Script::PrintTypedefs()
	{
		for (uint32_t i = 0; i < m_TypeDefinitions.Size; i++)
		{
			uint32_t columns[MONO_TYPEDEF_SIZE];
			mono_metadata_decode_row(m_TypeDefinitions.Table, i, columns, MONO_TYPEDEF_SIZE);

			const char* name = mono_metadata_string_heap(m_Image, columns[MONO_TYPEDEF_NAME]);
			const char* nameSpace = mono_metadata_string_heap(m_Image, columns[MONO_TYPEDEF_NAMESPACE]);

			CH_INFO("{}.{}", nameSpace, name);
		}
	}

	void Script::LoadTables()
	{
		m_TypeDefinitions.Table = mono_image_get_table_info(m_Image, MONO_TABLE_TYPEDEF);
		m_TypeDefinitions.Size = mono_table_info_get_rows(m_TypeDefinitions.Table);

		PrintTypedefs();
	}

}
