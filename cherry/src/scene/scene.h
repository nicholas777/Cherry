#pragma once

#include "graphics/cameras/camera.h"
#include "core/pointer.h"
#include "core/timestep.h"
#include "renderer/renderer2D.h"
#include "graphics/cameras/staticCamera.h"

#include "entt/entt.hpp"

namespace Cherry
{
    class Entity;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity CreateEntity(const std::string& name);
        void DeleteEntity(const Entity& entity);

        void OnRuntimeStart();
        void OnRuntimeStop();

        void OnUpdate(const Timestep& delta);
        void OnUpdate(const Timestep& delta, const Matrix4x4f& view, const Matrix4x4f& proj);

        Entity GetPrimaryCamera();
        Entity GetEntityByName(const std::string& name);

        static void Copy(Scene* dest, Scene* src);
    private:
        entt::registry m_Registry;

        friend class NativeScript;
        friend class Entity;
        friend class SceneSerializer;
        friend class SceneHierarchyPanel;
    };
}
