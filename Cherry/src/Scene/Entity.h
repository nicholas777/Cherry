#pragma once

#include "core/Core.h"
#include "Scene.h"

#include "../EnTT/entt.hpp"

namespace Cherry
{

	class CHERRY_API Entity
	{
	public:
		Entity(entt::entity handle, Scene* scene)
			: m_Handle(handle), m_Scene(scene) {}

		Entity(const Entity&) = default;

		template <typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.all_of<T>(m_Handle);
		}

		template <typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			CH_ASSERT(!HasComponent<T>(), "Entity already has this component");
			return m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
		}

		template <typename T>
		T& GetComponent()
		{
			CH_ASSERT(HasComponent<T>(), "Entity doesn't have component!");
			return m_Scene->m_Registry.get<T>(m_Handle);
		}

		template<typename T>
		void RemoveComponent()
		{
			CH_ASSERT(HasComponent<T>(), "Entity doesn't have component!");
			m_Scene->m_Registry.remove<T>(m_Handle);
		}

	private:
		entt::entity m_Handle;
		Scene* m_Scene;
	};

}