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

	static std::unordered_map<MonoType*, std::function<void(uint32_t)>> AddComponentFuncs{};
	static std::unordered_map<MonoType*, std::function<bool(uint32_t)>> HasComponentFuncs{};
	static std::unordered_map<MonoType*, std::function<void(uint32_t)>> RemoveComponentFuncs{};
	
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

	static uint32_t Scene_GetEntityByName(MonoString* name, bool* success)
	{
		Entity e = ScriptEngine::GetRuntimeScene()->GetEntityByName(ToString(name));
		*success = e.IsValid();
		return e;
	}

	static void Entity_HasComponent(uint32_t entity, MonoReflectionType* type, bool* result)
	{
		*result = HasComponentFuncs[mono_reflection_type_get_type(type)](entity);
	}

	static void Entity_AddComponent(uint32_t entity, MonoReflectionType* type)
	{
		AddComponentFuncs[mono_reflection_type_get_type(type)](entity);
	}

	static void Entity_RemoveComponent(uint32_t entity, MonoReflectionType* type)
	{
		RemoveComponentFuncs[mono_reflection_type_get_type(type)](entity);
	}

	static void NameComponent_GetName(uint32_t entity, MonoString** str)
	{
		*str = mono_string_new(ScriptEngine::GetMonoAppDomain(), Entity((entt::entity)entity, ScriptEngine::GetRuntimeScene()).GetComponent<NameComponent>().Name.c_str());
	}

	static void NameComponent_SetName(uint32_t entity, MonoString* str)
	{
		Entity((entt::entity)entity, ScriptEngine::GetRuntimeScene()).GetComponent<NameComponent>().Name = ToString(str);
	}

	static void TransformComponent_GetTranslation(uint32_t id, float* x, float* y)
	{
		Scene* scene = ScriptEngine::GetRuntimeScene();
		Vector2f translation = Entity((entt::entity)id, scene).GetComponent<TransformComponent>().Translation;
		*x = translation.x;
		*y = translation.y;
	}

	static void TransformComponent_SetTranslation(uint32_t id, float x, float y)
	{
		Scene* scene = ScriptEngine::GetRuntimeScene();
		Entity((entt::entity)id, scene).GetComponent<TransformComponent>().Translation = Vector2f(x, y);
	}

	static void TransformComponent_GetRotation(uint32_t id, float* rot)
	{
		Scene* scene = ScriptEngine::GetRuntimeScene();
		float rotation = Entity((entt::entity)id, scene).GetComponent<TransformComponent>().Rotation;
		*rot = rotation;
	}

	static void TransformComponent_SetRotation(uint32_t id, float rot)
	{
		Scene* scene = ScriptEngine::GetRuntimeScene();
		Entity((entt::entity)id, scene).GetComponent<TransformComponent>().Rotation = rot;
	}

	static void TransformComponent_GetScale(uint32_t id, float* x, float* y)
	{
		Scene* scene = ScriptEngine::GetRuntimeScene();
		Vector2f scale = Entity((entt::entity)id, scene).GetComponent<TransformComponent>().Scale;
		*x = scale.x;
		*y = scale.y;
	}

	static void TransformComponent_SetScale(uint32_t id, float x, float y)
	{
		Scene* scene = ScriptEngine::GetRuntimeScene();
		Entity((entt::entity)id, scene).GetComponent<TransformComponent>().Scale = Vector2f(x, y);
	}

	class ScriptAPI
	{
	public:
		static void Init()
		{
			RegisterEntityFuncs();

			ADD_INTERNAL_CALL(InputIsKeyDown);
			ADD_INTERNAL_CALL(InputIsMouseDown);
			ADD_INTERNAL_CALL(InputGetMousePos);

			ADD_INTERNAL_CALL(Scene_GetEntityByName);

			ADD_INTERNAL_CALL(Entity_HasComponent);
			ADD_INTERNAL_CALL(Entity_AddComponent);
			ADD_INTERNAL_CALL(Entity_RemoveComponent);

			ADD_INTERNAL_CALL(NameComponent_GetName);
			ADD_INTERNAL_CALL(NameComponent_SetName);

			ADD_INTERNAL_CALL(TransformComponent_GetTranslation);
			ADD_INTERNAL_CALL(TransformComponent_SetTranslation);
			ADD_INTERNAL_CALL(TransformComponent_GetRotation);
			ADD_INTERNAL_CALL(TransformComponent_SetRotation);
			ADD_INTERNAL_CALL(TransformComponent_GetScale);
			ADD_INTERNAL_CALL(TransformComponent_SetScale);
		}

	private:
		static void RegisterEntityFuncs()
		{
			RegisterEntityFunc<NameComponent>("Cherry.NameComponent");
			RegisterEntityFunc<TransformComponent>("Cherry.TransformComponent");
			RegisterEntityFunc<SpriteComponent>("Cherry.SpriteComponent");
			RegisterEntityFunc<CameraComponent>("Cherry.CameraComponent");
			// RegisterEntityFuns<ScriptComponent>("Cherry.ScriptComponent");
			// RegisterEntityFuns<NativeScriptComponent>("Cherry.NativeScriptComponent");
		}

		template <typename T>
		static void RegisterEntityFunc(char* name)
		{
			MonoImage* image = ScriptEngine::GetMonoCoreImage();
			MonoType* type = mono_reflection_type_from_name(name, image);
			
			std::function<bool(uint32_t)> hasCompFunc = [](uint32_t entity) { return Entity((entt::entity)entity, ScriptEngine::GetRuntimeScene()).HasComponent<T>(); };
			HasComponentFuncs[type] = hasCompFunc;
			
			std::function<void(uint32_t)> addCompFunc = [](uint32_t entity) { Entity((entt::entity)entity, ScriptEngine::GetRuntimeScene()).AddComponent<T>(); };
			AddComponentFuncs[type] = addCompFunc;

			std::function<void(uint32_t)> removeCompFunc = [](uint32_t entity) { Entity((entt::entity)entity, ScriptEngine::GetRuntimeScene()).RemoveComponent<T>(); };
			RemoveComponentFuncs[type] = removeCompFunc;
		}
	};
}
