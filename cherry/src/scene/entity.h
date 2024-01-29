#pragma once

#include "core/log.h"
#include "scene.h"

#include <entt/entt.hpp>

namespace Cherry {

    class Entity
    {
    public:
        Entity(): m_Handle(entt::null), m_Scene(nullptr) {}

        Entity(entt::entity handle, Scene* scene): m_Handle(handle), m_Scene(scene) {}

        bool IsValid() const {
            if (m_Scene)
                return m_Scene->m_Registry.valid(m_Handle);
            return false;
        }

        template<typename T>
        bool HasComponent() const {
            return m_Scene->m_Registry.all_of<T>(m_Handle);
        }

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args) const {
            CH_ASSERT(!HasComponent<T>(), "Entity already has this component");
            return m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
        }

        template<typename T>
        T& GetComponent() const {
            CH_ASSERT(HasComponent<T>(), "Entity doesn't have component!");
            return m_Scene->m_Registry.get<T>(m_Handle);
        }

        template<typename T>
        void RemoveComponent() const {
            CH_ASSERT(HasComponent<T>(), "Entity doesn't have component!");
            m_Scene->m_Registry.remove<T>(m_Handle);
        }

        bool operator==(const Entity& other) const {
            return other.m_Handle == m_Handle && m_Scene == other.m_Scene;
        }

        operator uint32_t() const { return (uint32_t)m_Handle; }

        operator entt::entity() const { return m_Handle; }

        operator bool() const { return m_Handle != entt::null && m_Scene != nullptr; }

        uint32_t GetHandle() { return (uint32_t)m_Handle; };

        static void Delete(const Entity& entity) { entity.m_Scene->DeleteEntity(entity); }

    private:
        entt::entity m_Handle;
        Scene* m_Scene;

        friend class Scene;
        friend class EntityDeleteAction;
    };

}
