#include "epch.h"

#include "Scene.h"
#include "Entity.h"
#include "Component.h"
#include "Script.h"

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

	void Scene::DeleteEntity(const Entity& entity)
	{
		m_Registry.destroy(entity);
	}

	// TODO: Resizing camera viewport
	void Scene::OnUpdate(const Timestep& delta)
	{
		RenderCommand::Clear();

		Camera* mainCamera = nullptr;
		Matrix4x4f cameraTransform;

		{
			m_Registry.view<ScriptComponent>().each([=](auto entity, auto& scriptExecutor)
			{
				if (!scriptExecutor.script)
				{
					scriptExecutor.CreateInstanceFn();
					scriptExecutor.script->m_Entity = Entity(entity, this);
					scriptExecutor.OnCreateFn(scriptExecutor.script);
				}

				scriptExecutor.OnUpdateFn(scriptExecutor.script, delta);
			});
		}

		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();

			for (auto& entity : view)
			{
				auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.IsPrimary)
				{
					mainCamera = &camera.camera;
					cameraTransform = transform.GetMatrix();
					break;
				}
			}
		}
		
		{
			if (mainCamera)
			{
				Renderer2D::Begin(mainCamera, cameraTransform);

				auto group = m_Registry.group<TransformComponent>(entt::get<SpriteComponent>);

				for (auto& entity : group)
				{
					auto& [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);

					if (sprite.UseTexture)
					{
						Renderer2D::DrawRect(transform.GetMatrix(), sprite.SpriteTexture, sprite.Color);
					}
					else
					{
						Renderer2D::DrawRect(transform.GetMatrix(), sprite.Color);
					}
				}

				Renderer2D::End();
			}
		}
	}
}
