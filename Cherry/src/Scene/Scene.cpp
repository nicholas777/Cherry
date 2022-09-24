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
				Renderer2D::Begin(mainCamera->GetProjection(), cameraTransform);

				auto group = m_Registry.group<TransformComponent>(entt::get<SpriteComponent>);

				for (auto& entity : group)
				{
					auto& [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);

					if (sprite.UseTexture)
					{
						if (sprite.SpriteTexture.IsAlive())
							Renderer2D::DrawRect(transform.GetMatrix(), *sprite.SpriteTexture, sprite.Color);
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

	void Scene::OnUpdate(const Timestep& delta, const StaticCamera& camera)
	{
		RenderCommand::Clear();
		Renderer2D::Begin(camera.GetProjection(), camera.GetTransform());

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
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteComponent>);

			for (auto& entity : group)
			{
				auto& [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);

				if (sprite.UseTexture)
				{
					if (sprite.SpriteTexture.IsAlive())
						Renderer2D::DrawRect(transform.GetMatrix(), *sprite.SpriteTexture, sprite.Color);
				}
				else
				{
					Renderer2D::DrawRect(transform.GetMatrix(), sprite.Color);
				}
			}
		}

		Renderer2D::End();
	}

	Entity Scene::GetPrimaryCamera()
	{
		auto view = m_Registry.view<CameraComponent>();

		for (auto entity : view)
		{
			auto& comp = view.get<CameraComponent>(entity);

			if (comp.IsPrimary)
				return Entity(entity, this);
		}
		return {};
	}
	
	Entity Scene::GetEntityByName(const std::string& name)
	{
		auto view = m_Registry.view<NameComponent>();

		for (auto entity : view)
		{
			if (view.get<NameComponent>(entity).Name == name)
				return Entity(entity, this);
		}

		return Entity();
	}
}
