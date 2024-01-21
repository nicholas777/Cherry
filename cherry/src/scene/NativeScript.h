#pragma once

#include "entity.h"

namespace Cherry
{
	class NativeScript
	{
	public:
		NativeScript() = default;

		template<typename T>
		bool HasComponent()
		{
			return m_Entity.HasComponent<T>();
		}

		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

		template<typename T, typename... Args>
		T& AddComponent(Args... args)
		{
			return m_Entity.AddComponent<T>(args...);
		}

		template<typename T>
		T& RemoveComponent()
		{
			return m_Entity.RemoveComponent<T>();
		}

	private:
		Entity m_Entity;
		friend class Scene;
	};
}
