#include "epch.h"
#include "Class.h"
#include "core/Log.h"

#include <mono/metadata/tabledefs.h>

namespace Cherry
{
	Class::Class(MonoClass* c)
	{
		m_Class = c;
	}

	Class::~Class()
	{
		
	}

	// TODO: Generating from non-default constructors 
	Shared<Object> Class::Instantiate(MonoDomain* domain)
	{
		MonoObject* obj = mono_object_new(domain, m_Class);
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

	void* Method::GetMethodThunk()
	{
		return mono_method_get_unmanaged_thunk(m_Method);
	}

	Object::~Object()
	{

	}

	static ScriptFieldType MonoTypeToScriptFieldType(MonoType* type)
	{
		const char* name = mono_type_get_name(type);
		CH_TRACE(name);
		if (strcmp(name, "System.Single") == 0)
			return ScriptFieldType::Float;
		else if (strcmp(name, "System.Double") == 0)
			return ScriptFieldType::Double;
		else if (strcmp(name, "System.Int32") == 0)
			return ScriptFieldType::Int;
		else if (strcmp(name, "System.UInt32") == 0)
			return ScriptFieldType::UInt;
		else if (strcmp(name, "System.Boolean") == 0)
			return ScriptFieldType::Bool;
		else if (strcmp(name, "System.Int16") == 0)
			return ScriptFieldType::Short;
		else if (strcmp(name, "System.UInt16") == 0)
			return ScriptFieldType::UShort;
		else if (strcmp(name, "System.Int64") == 0)
			return ScriptFieldType::Long;
		else if (strcmp(name, "System.UInt64") == 0)
			return ScriptFieldType::ULong;
		else if (strcmp(name, "System.Byte") == 0)
			return ScriptFieldType::Byte;

		else if (strcmp(name, "System.String") == 0)
			return ScriptFieldType::String;

		else if (strcmp(name, "Cherry.Vector2") == 0)
			return ScriptFieldType::Vector2;
		else if (strcmp(name, "Cherry.Vector3") == 0)
			return ScriptFieldType::Vector3;
		else if (strcmp(name, "Cherry.Vector4") == 0)
			return ScriptFieldType::Vector4;

		return ScriptFieldType::None;
	}

	Field::Field(MonoClassField* field, MonoClass* c)
	{
		
		m_Field = field;
		m_Class = c;
		
		m_Name = mono_field_get_name(field);
		m_MonoType = mono_field_get_type(field);
		m_Type = MonoTypeToScriptFieldType(m_MonoType);

		uint32_t flags = mono_field_get_flags(field);
		switch (flags)
		{
			case FIELD_ATTRIBUTE_PUBLIC:
				m_Access = Accessibility::Public;
				break;
			case FIELD_ATTRIBUTE_PRIVATE:
				m_Access = Accessibility::Private;
				break;
			case FIELD_ATTRIBUTE_ASSEMBLY:
				m_Access = Accessibility::Internal;
				break;
			case FIELD_ATTRIBUTE_FAMILY:
				m_Access = Accessibility::Protected;
				break;
			case FIELD_ATTRIBUTE_FAM_AND_ASSEM:
				m_Access = Accessibility::Internal | Accessibility::Protected;
				break;
			case FIELD_ATTRIBUTE_FAM_OR_ASSEM:
				m_Access = Accessibility::Internal | Accessibility::Protected;
				break;
		}
	}

	bool Field::IsIntegralType()
	{
		return
			m_Type != ScriptFieldType::Bool &&
			m_Type != ScriptFieldType::Vector2 &&
			m_Type != ScriptFieldType::Vector3 &&
			m_Type != ScriptFieldType::Vector4;
	}
}
