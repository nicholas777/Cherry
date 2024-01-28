#pragma once

#include "core/pointer.h"
#include "scene/entity.h"

#include <entt/entt.hpp>

extern "C" {
    #include <lualib.h>
}

#include <vector>

namespace Cherry {
    class Entity;
    class Scene;

    class Field {};

    class ScriptEngine
    {
    public:
        static void Init();
        static void Shutdown();

        static Scene* GetRuntimeScene();
        static void OnRuntimeStart(Scene* scene);
        static void OnRuntimeStop();

        static void UpdateScriptedEntities(float delta);
        static void RegisterScriptedEntity(const Entity& e);
        static void ReloadScripts();

        static void InitScriptedEntity(Entity e);

        static bool IsScriptClass(const std::string& table);
        static std::vector<Shared<Field>>* ScriptClassGetFields(const std::string& table);

    private:
        typedef void* OnCreateFunc;
        typedef void* OnUpdateFunc;
        typedef void* OnDestroyFunc;

        struct ScriptedEntity {
            OnCreateFunc OnCreate = nullptr;
            OnUpdateFunc OnUpdate = nullptr;
            OnDestroyFunc OnDestroy = nullptr;
            entt::entity entity;
        };

        static std::vector<ScriptedEntity> m_ScriptedEntities;

        static void UnloadScriptedEntities();
    private:
        static lua_State* m_State;
        static Scene* m_RuntimeScene;
        static const char* m_ScriptDir;
    };
}
