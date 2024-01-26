#pragma once

#include "core/pointer.h"
#include "script.h"

#include <lualib.h>
#include <entt/entt.hpp>

namespace Cherry 
{
    class Entity;
    class Scene;

    class ScriptEngine
    {
    public:
        static void Init();
        static void Shutdown();

        static Scene* GetRuntimeScene();
        static void OnRuntimeStart(Scene* scene);
        static void OnRuntimeStop();

        static void UpdateScriptedEntities(float delta);

    private:
        struct ScriptedEntity
        {
            OnCreateFunc OnCreate = nullptr;
            OnUpdateFunc OnUpdate = nullptr;
            OnDestroyFunc OnDestroy = nullptr;
            entt::entity entity;
        };

        static std::vector<ScriptedEntity> m_ScriptedEntities;

        static void UnloadScriptedEntities();
    private:
        static lua_State* m_State;
    };
}
