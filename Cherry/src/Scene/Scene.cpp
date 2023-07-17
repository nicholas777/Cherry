#include "epch.h"

#include "Scene.h"
#include "Entity.h"
#include "Component.h"
#include "NativeScript.h"
#include "Debug/Profiler.h"
#include "Scripting/ScriptEngine.h"

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
		CH_PROFILE_FUNC();

		Entity entity = Entity(m_Registry.create(), this);
		entity.AddComponent<NameComponent>(name);

		return entity;
	}

	void Scene::DeleteEntity(const Entity& entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::OnRuntimeStart()
	{
		ScriptEngine::OnRuntimeStart(this);

		m_Registry.view<ScriptComponent>().each([=](auto entity, auto& script)
		{
			ScriptEngine::InitScriptedEntity(Entity(entity, this));
		});
	}

	void Scene::OnRuntimeStop()
	{
		ScriptEngine::OnRuntimeStop();
	}

	// TODO: Resizing camera viewport
	void Scene::OnUpdate(const Timestep& delta)
	{
		CH_PROFILE_FUNC();

		RenderCommand::Clear();

		Camera* mainCamera = nullptr;
		Matrix4x4f cameraTransform;

		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& scriptExecutor)
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

		ScriptEngine::UpdateScriptedEntities(delta.GetMilliseconds());

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

	// TODO: Proper system for scene rendering
	void Scene::OnUpdate(const Timestep& delta, const StaticCamera& camera)
	{
		CH_PROFILE_FUNC();

		RenderCommand::Clear();
		Renderer2D::Begin(camera.GetProjection(), camera.GetTransform());

		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& scriptExecutor)
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
					if (sprite.SpriteTexture->texture.IsAlive())
						Renderer2D::DrawRect(transform.GetMatrix(), *sprite.SpriteTexture, sprite.Color, (uint32_t)entity);
				}
				else
				{
					Renderer2D::DrawRect(transform.GetMatrix(), sprite.Color, (uint32_t)entity);
				}
			}
		}

		Renderer2D::End();
	}

	Entity Scene::GetPrimaryCamera()
	{
		CH_PROFILE_FUNC();

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
		CH_PROFILE_FUNC();

		auto view = m_Registry.view<NameComponent>();

		for (auto entity : view)
		{
			if (view.get<NameComponent>(entity).Name == name)
				return Entity(entity, this);
		}

		return Entity();
	}

	template <typename... Components>
	static void CopyComponents(ComponentList<Components...>, entt::registry& src, entt::registry& dest, std::unordered_map<std::string, entt::entity>& entities)
	{
		([&]
		{
			auto view = src.view<Components>(); 
			for (auto entity : view)
			{
				auto DestEntity = entities[src.get<NameComponent>(entity).Name];
				auto comp = src.get<Components>(entity);

				dest.emplace_or_replace<Components>(DestEntity, comp);
			}
		} (), ...);
	}

	void Scene::Copy(Scene* dest, Scene* src)
	{
		// Creating the entities
		dest->m_Registry.clear();

		std::unordered_map<std::string, entt::entity> entities{};
		auto& nameView = src->m_Registry.view<NameComponent>();
		for (auto e : nameView)
		{
			const std::string& name = src->m_Registry.get<NameComponent>(e).Name;
			Entity entity = dest->CreateEntity(name);
			entities[name] = entity;
		}

		CopyComponents(OptionalComponents{}, src->m_Registry, dest->m_Registry, entities);
	}
}
