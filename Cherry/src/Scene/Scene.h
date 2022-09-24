#pragma once

#include "Graphics/Cameras/Camera.h"
#include "core/Pointer.h"
#include "core/Timestep.h"
#include "Renderer/Renderer2D.h"
#include "Graphics/Cameras/StaticCamera.h"

#include "entt.hpp"

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

		void OnUpdate(const Timestep& delta);
		void OnUpdate(const Timestep& delta, const StaticCamera& camera);

		Entity GetPrimaryCamera();
		Entity GetEntityByName(const std::string& name);
	private:
		entt::registry m_Registry;

		friend class Script;
		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};
}
