#pragma once

#include "core/pointer.h"

#include <mono/metadata/assembly.h>
#include <mono/jit/jit.h>

namespace Cherry
{
	class Object;
	class Method;

	class Class
	{
	public:
		Class() = default;
		Class(MonoClass* c, MonoDomain* appDomain);
		~Class();

		Shared<Object> Instantiate();
		Shared<Method> GetMethod(const char* name, int params);

	private:
		MonoClass* m_Class = nullptr;
		MonoDomain* m_AppDomain = nullptr;
	};

	class Object
	{
	public:
		Object() = default;
		Object(MonoObject* obj, MonoClass* c)
			: m_Object(obj), m_Class(c) {};
		~Object() { delete m_Object; };

	private:
		MonoObject* m_Object;
		MonoClass* m_Class;

		friend class Method;
	};

	class Method
	{
	public:
		Method() = default;
		Method(MonoMethod* method, int paramCount)
			: m_Method(method), m_ParamCount(paramCount) {};
		~Method() { delete m_Method; };

		template <typename... Args>
		void Invoke(Shared<Object> obj, Args... args)
		{
			MonoObject* exception = nullptr;
			mono_runtime_invoke(m_Method, obj.Get(), nullptr, &exception);
		}

	private:
		MonoMethod* m_Method = nullptr;
		int m_ParamCount = 0;
	};
}
