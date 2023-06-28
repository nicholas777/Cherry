#pragma once

#include "core/pointer.h"

#include <mono/metadata/assembly.h>
#include <mono/jit/jit.h>

namespace Cherry
{
	class Object;
	class Method;
	class Field;

	class Class
	{
	public:
		Class() = default;
		Class(MonoClass* c, MonoDomain* appDomain);
		~Class();

		Shared<Object> Instantiate();
		Shared<Method> GetMethod(const char* name, int params);
		Shared<Field> GetField(const char* name);

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
		~Object();

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
		~Method();

		template <typename... Args>
		void Invoke(Shared<Object> obj, Args... args)
		{
			void* data = reinterpret_cast<void*>(std::addressof(args)...);

			MonoObject* exception = nullptr;
			mono_runtime_invoke(m_Method, obj.Get(), &data, &exception);
		}

		void Invoke(Shared<Object> obj) 
		{
			MonoObject* exception = nullptr;
			mono_runtime_invoke(m_Method, obj.Get(), nullptr, &exception);
		}

	private:
		MonoMethod* m_Method = nullptr;
		int m_ParamCount = -1;
	};

	enum class Accessibility : uint8_t
	{
		None		= 0,
		Private		= (1 << 0),
		Internal	= (1 << 1),
		Protected	= (1 << 2),
		Public		= (1 << 3)
	};

	class Field
	{
	public:
		Field() = default;
		Field(MonoClassField* field, MonoClass* c);
	private:
		MonoClassField* m_Field = nullptr;
		MonoClass* m_Class = nullptr;

		Accessibility m_Access = Accessibility::None;

		void GetAccessibility();
	};
}
