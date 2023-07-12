#pragma once

#include "core/Core.h"
#include "Events/Input.h"
#include "Scene/Entity.h"
#include "Scene/Component.h"

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

	static bool InputIsKeyDown(Key key)
	{
		return Input::GetKeyPressed(key);
	}

	static bool InputIsMouseDown(MouseButton button)
	{
		return Input::GetMouseDown(button);
	}

	static Vector2f InputGetMousePos()
	{
		Vector2i vec = Input::GetMousePosRaw();
		return Vector2f(vec.x, vec.y);
	}

	static void GetEntityTranslation(uint32_t id, float* x, float* y)
	{
		Scene* scene = ScriptEngine::GetRuntimeScene();
		Vector2f translation = Entity((entt::entity)id, scene).GetComponent<TransformComponent>().Translation;
		*x = translation.x;
		*y = translation.y;
	}

	static void SetEntityTranslation(uint32_t id, Vector2f vec)
	{
		Scene* scene = ScriptEngine::GetRuntimeScene();
		Entity((entt::entity)id, scene).GetComponent<TransformComponent>().Translation = vec;
	}

	class ScriptAPI
	{
	public:
		static void Init()
		{
			ADD_INTERNAL_CALL(InputIsKeyDown);
			ADD_INTERNAL_CALL(InputIsMouseDown);
			ADD_INTERNAL_CALL(InputGetMousePos);

			ADD_INTERNAL_CALL(GetEntityTranslation);
			ADD_INTERNAL_CALL(SetEntityTranslation);
		}
	};
}
