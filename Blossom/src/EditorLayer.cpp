#include "EditorLayer.h"

namespace Cherry
{
	EditorLayer::~EditorLayer()
	{
	}

	void EditorLayer::OnAttach()
	{
		
		
		float aspect = WINDOW_WIDTH / WINDOW_HEIGHT;
		
		m_EditorCamera = new Camera({0, 0}, -aspect, aspect, 1, -1, -1, 1);
		m_LevelEditorCamera = new Camera({ 0, 0 }, -aspect, aspect, 1, -1, -1, 1);
		m_LevelEditorCameraController = new CameraController(m_LevelEditorCamera.Get(), -0.002f);
		
		m_Font = new Font("assets/Goldfish.ttf", 24);
		m_SceneHierarchyPanel = new SceneHierarchyPanel(m_Font);

		m_Scene = new Scene;

		Entity e = m_Scene->CreateEntity();

		TextureParams params;
		params.format = TextureFormat::Auto;
		params.minFilter = TextureFilter::Linear;
		params.magFilter = TextureFilter::Nearest;
		params.wrap = TextureWrap::Repeat;

		m_SmileTexture = Texture::Create("assets/Smile.png", params);
		e.AddComponent<SpriteComponent>();
		e.GetComponent<SpriteComponent>().SpriteTexture = m_SmileTexture.Get();
		e.AddComponent<TransformComponent>(Matrix4x4f(1.0f));

		RenderCommand::SetClearColor({1, 0, 0, 1});
	}

	void EditorLayer::OnUpdate(const Timestep& delta)
	{
		RenderCommand::Clear();

		m_LevelEditorCameraController->Update(delta.GetMilliseconds());
		Renderer2D::Begin(m_LevelEditorCamera.Get());
		m_Scene->OnUpdate(delta);
		Renderer2D::End();

		Renderer2D::Begin(m_EditorCamera.Get());
		m_SceneHierarchyPanel->OnUpdate();
		Renderer2D::End();
	}

}

