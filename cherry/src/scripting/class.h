#pragma once

#include "core/pointer.h"

#include <mono/metadata/assembly.h>
#include <mono/jit/jit.h>

namespace Cherry
{
	class Object;
	class Method;
	class Field;

	typedef void (*OnCreateFunc)(MonoObject*, MonoException**);
	typedef void (*OnUpdateFunc)(MonoObject* , float, MonoException**);
	typedef void (*OnDestroyFunc)(MonoObject*, MonoException**);
	
	class Class
	{
	public:
		Class() = default;
		Class(MonoClass* c);
		~Class();

		Shared<Object> Instantiate(MonoDomain* domain);
		Shared<Method> GetMethod(const char* name, int params);
		Shared<Method> GetMethodIfExists(const char* name, int params);
		Shared<Field> GetField(const char* name);

		MonoClass* GetMonoClass() { return m_Class; };

	private:
		MonoClass* m_Class = nullptr;
	};

	class Object
	{
	public:
		Object() = default;
		Object(MonoObject* obj, MonoClass* c)
			: m_Object(obj), m_Class(c) {};
		~Object();

		MonoObject* GetMonoObject() { return m_Object; };

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

		void* GetMethodThunk();

		template <typename Arg, typename... Args>
		void Invoke(Shared<Object> obj, Arg arg, Args... args)
		{
			void* data = &arg;

			MonoObject* exception = nullptr;
			mono_runtime_invoke(m_Method, obj->GetMonoObject(), &data, &exception);
		}

		void Invoke(Shared<Object> obj) 
		{
			MonoObject* exception = nullptr;
			mono_runtime_invoke(m_Method, obj->GetMonoObject(), nullptr, &exception);
		}

	private:
		MonoMethod* m_Method = nullptr;
		int m_ParamCount = -1;
	};

	enum Accessibility : uint8_t
	{
		None		= 0,
		Private		= (1 << 0),
		Internal	= (1 << 1),
		Protected	= (1 << 2),
		Public		= (1 << 3)
	};

	enum class ScriptFieldType
	{
		None = 0,
		Int, UInt, Float, Double, Short, UShort, Byte, Long, ULong, Bool,
		Vector2, Vector3, Vector4, String
	};

	class Field
	{
	public:
		Field() = default;
		Field(MonoClassField* field, MonoClass* c);

		const char* GetName() { return m_Name; };
		uint8_t GetAccessibility() { return m_Access; };
		ScriptFieldType GetType() { return m_Type; };
		MonoType* GetMonoType() { return m_MonoType; };

		bool IsIntegralType();

		template <typename T>
		void GetData(Shared<Object> obj, T* value) 
		{
			mono_field_get_value(obj->GetMonoObject(), m_Field, (void*)value);
		}

		void GetData(Shared<Object> obj, const char** value)
		{
			MonoString* str;
			mono_field_get_value(obj->GetMonoObject(), m_Field, &str);
			char* temp = mono_string_to_utf8(str);
			if (temp == nullptr)
			{
				*value = "";
				return;
			}

			strcpy((char*)*value, temp);
			mono_free(temp);
		}

		template <typename T>
		void SetData(Shared<Object> obj, const T& data)
		{
			mono_field_set_value(obj->GetMonoObject(), m_Field, (void*)&data);
		}
		
		void SetData(Shared<Object> obj, const char* data)
		{
			MonoString* str = mono_string_new(mono_object_get_domain(obj->GetMonoObject()), data);
			mono_field_set_value(obj->GetMonoObject(), m_Field, str);
		}

	private:
		MonoClassField* m_Field = nullptr;
		MonoClass* m_Class = nullptr;

		// Field info

		uint8_t m_Access = Accessibility::None;
		const char* m_Name;
		ScriptFieldType m_Type;
		MonoType* m_MonoType;
	};
}
