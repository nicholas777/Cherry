#include "epch.h"
#include "Class.h"



namespace Cherry
{
	Class::Class(MonoClass* c, MonoDomain* appDomain)
	{
		m_Class = c;
		m_AppDomain = appDomain;
	}

	Class::~Class()
	{
		delete m_Class;
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
}
