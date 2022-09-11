#include "epch.h"

#include "Scene.h"
#include "Entity.h"

namespace Cherry
{
	Scene::Scene()
	{
		
	}

	Scene::~Scene()
	{
		
	}

	// TODO: Events for creating and updating entities
	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = Entity(m_Registry.create(), this);
		entity.AddComponent<NameComponent>(name);

		return entity;
	}

	void Scene::OnUpdate(const Timestep& delta)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteComponent>);

		for (auto& entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);

			if (sprite.SpriteTexture)
			{
				Renderer2D::DrawRect(transform.GetMatrix(), sprite.SpriteTexture);
			}
			else
			{
				Renderer2D::DrawRect(transform.GetMatrix(), sprite.Color);
			}
		}
	}
}
