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

        static void InitScriptedEntity(Entity e);

        static void UpdateScriptedEntities(float delta);
        static void RegisterScriptedEntity(const Entity& e);
        static void ReloadScripts();

        static bool IsScriptClass(const std::string& table);
        static std::vector<Shared<Field>>* ScriptClassGetFields(const std::string& table);

    private:
        struct ScriptClass {
            const char* name;
            bool onCreate = false, onUpdate = false, onDestroy = false;
            int luaNewMethod = -1;
        };

        static std::vector<ScriptClass> m_ScriptClasses;

    private:
        typedef int OnCreateFunc;
        typedef int OnUpdateFunc;
        typedef int OnDestroyFunc;

        struct ScriptedEntity {
            OnCreateFunc OnCreate = -1;
            OnUpdateFunc OnUpdate = -1;
            OnDestroyFunc OnDestroy = -1;
            int luaTable = -1;
            entt::entity entity;
        };

        static std::vector<ScriptedEntity> m_ScriptedEntities;
    private:
        static lua_State* m_State;
        static Scene* m_RuntimeScene;
        static const char* m_ScriptDir;
    };
}
