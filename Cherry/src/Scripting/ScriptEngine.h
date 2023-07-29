#pragma once

#include "core/Pointer.h"
#include "Script.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

#include <entt.hpp>

namespace Cherry 
{
	class Entity;
	class Scene;

	class ScriptEngine
	{
	public:
		static void Init();
		static void Shutdown();

		static Shared<Assembly> LoadAssembly(std::string path);

		static void InitScriptedEntity(Entity entity);
		static const std::vector<Shared<Field>>* ScriptClassGetFields(const char* c);
		static bool IsScriptClass(const char* name);
		static Shared<Object> GetScriptedEntity(Entity entity);
		static void RegisterScriptedEntity(Entity entity);

		static Scene* GetRuntimeScene();
		static void OnRuntimeStart(Scene* scene);
		static void OnRuntimeStop();

		static void UpdateScriptedEntities(float delta);

		static void ReloadAssemblies();
		static MonoImage* GetMonoCoreImage() { return m_CoreAssembly->m_Image; };
		static MonoDomain* GetMonoAppDomain() { return m_AppDomain; };
	private:
		struct ScriptedEntity
		{
			OnCreateFunc OnCreate = nullptr;
			OnUpdateFunc OnUpdate = nullptr;
			OnDestroyFunc OnDestroy = nullptr;
			Shared<Object> Instance = nullptr;
			entt::entity entity;
		};

		static std::vector<ScriptedEntity> m_ScriptedEntities;

		static void UnloadScriptedEntities();
	private:
		static void LoadEntityClasses();

		struct EntityClass
		{
			Shared<Class> klass = nullptr;
			OnCreateFunc OnCreate = nullptr;
			OnUpdateFunc OnUpdate = nullptr;
			OnDestroyFunc OnDestroy = nullptr;

			std::vector<Shared<Field>> fields{};
		};
		static std::unordered_map<std::string, EntityClass> m_EntityClasses;
	private:

		static const char* m_GameDLLPath;

		static MonoDomain* m_RootDomain;
		static MonoDomain* m_AppDomain;

		static Shared<Assembly> m_CoreAssembly;
		static Shared<Assembly> m_GameAssembly;

		static Shared<Class> m_EntityClass;

		static void InitScriptingSystem();

		static void CreateAppDomain();
		static void UnloadAppDomain();

	};
}
