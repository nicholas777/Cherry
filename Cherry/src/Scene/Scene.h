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

		void OnRuntimeStart();
		void OnRuntimeStop();

		void OnUpdate(const Timestep& delta);
		void OnUpdate(const Timestep& delta, const StaticCamera& camera);

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
