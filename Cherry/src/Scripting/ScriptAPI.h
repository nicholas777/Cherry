#pragma once

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

#define ADD_INTERNAL_CALL(name) mono_add_internal_call((std::string("Cherry.Internal::") + #name).c_str() , name)

namespace Cherry
{
	static std::string ToString(MonoString* str)
	{
		char* c_str = mono_string_to_utf8(str);
		std::string result(c_str);
		mono_free(c_str);
		return result;
	}

	// Logging

	static void Trace(MonoString* str)
	{

	}

	class ScriptAPI
	{
	public:
		static void Init()
		{
			// Logging
			ADD_INTERNAL_CALL(Trace);
		}
	};
}
