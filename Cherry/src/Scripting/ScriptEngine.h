#pragma once

#include "core/Pointer.h"
#include "Script.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

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
		static bool IsScriptClass(const char* name);

		static Scene* GetRuntimeScene();
		static void OnRuntimeStart(Scene* scene);
		static void OnRuntimeStop();

	private:
		static void LoadEntityClasses();

		struct EntityClass
		{
			Shared<Class> klass = nullptr;
			Shared<Method> OnCreate = nullptr;
			Shared<Method> OnUpdate = nullptr;
			Shared<Method> OnDestroy = nullptr;
		};
		static std::unordered_map<std::string, EntityClass> m_EntityClasses;
	private:

		static MonoDomain* m_RootDomain;
		static MonoDomain* m_AppDomain;

		static Shared<Assembly> m_CoreAssembly;
		static Shared<Assembly> m_GameAssembly;

		static Shared<Class> m_EntityClass;
	};
}
