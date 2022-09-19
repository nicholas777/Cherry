#pragma once

#include "Graphics/Cameras/Camera.h"
#include "core/Pointer.h"
#include "core/Timestep.h"
#include "Renderer/Renderer2D.h"
#include "AssetManager.h"

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

		uint32_t CreateTexture(const std::string& filepath, TextureParams params = TextureParams());
		TextureAsset& GetTexture(uint32_t id);
	private:
		entt::registry m_Registry;
		AssetManager m_AssetManager;

		friend class Script;
		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};
}
