#include "epch.h"
#include "Class.h"
#include "core/Log.h"

namespace Cherry
{
	Class::Class(MonoClass* c, MonoDomain* appDomain)
	{
		m_Class = c;
		m_AppDomain = appDomain;
	}

	Class::~Class()
	{
		
	}

	// TODO: Generating from non-default constructors 
	Shared<Object> Class::Instantiate()
	{
		MonoObject* obj = mono_object_new(m_AppDomain, m_Class);
		CH_VALIDATE(obj);

		mono_runtime_object_init(obj);

		return new Object(obj, m_Class);
	}

	Shared<Method> Class::GetMethod(const char* name, int params)
	{
		MonoMethod* method = mono_class_get_method_from_name(m_Class, name, params);
		CH_VALIDATE(method);

		return new Method(method, params);
	}

	Shared<Method> Class::GetMethodIfExists(const char* name, int params)
	{
		MonoMethod* method = mono_class_get_method_from_name(m_Class, name, params);
		
		if (method)
		{
			return new Method(method, params);
		}
		else
		{
			return nullptr;
		}
	}

	Shared<Field> Class::GetField(const char* name)
	{
		return new Field(
			mono_class_get_field_from_name(m_Class, name),
			m_Class
		);
	}

	Method::~Method()
	{
		
	}

	Object::~Object()
	{

	}

	Field::Field(MonoClassField* field, MonoClass* c)
	{
		m_Field = field;
		m_Class = c;

		GetAccessibility();
	}

	void Field::GetAccessibility()
	{
		//uint8_t accessFlag = mono_field_get_flags(m_Field) & MONO_FIELD_ATTRIBUTE_PUBLIC;
	}
}
