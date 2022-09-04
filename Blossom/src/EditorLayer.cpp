#include "EditorLayer.h"

namespace Cherry
{
	EditorLayer::~EditorLayer()
	{
	}

	void EditorLayer::OnAttach()
	{
		TextureParams params;
		params.format = TextureFormat::Auto;
		params.minFilter = TextureFilter::Linear;
		params.magFilter = TextureFilter::Nearest;
		params.wrap = TextureWrap::Repeat;

		m_SmileTexture = Texture::Create("assets/Smile.png", params);
		float height = Application::GetApplication().GetWindow()->GetHeight();
		float width =  Application::GetApplication().GetWindow()->GetWidth();
		
		float aspect = width / height;
		
		m_EditorCamera = new Camera({0, 0}, -aspect, aspect, 1, -1, -1, 1);
		m_LevelEditorCamera = new Camera({ 0, 0 }, -aspect, aspect, 1, -1, -1, 1);
		m_LevelEditorCameraController = new CameraController(m_LevelEditorCamera.Get(), -0.002f);
		
		m_Font = new Font("assets/Goldfish.ttf", 24);

		RenderCommand::SetClearColor({1, 0, 0, 1});
	}

	void EditorLayer::OnUpdate(const Timestep& delta)
	{
		RenderCommand::Clear();

		m_LevelEditorCameraController->Update(delta.GetMilliseconds());
		Renderer2D::Begin(m_LevelEditorCamera.Get());
		Renderer2D::DrawRect({ 0, 0 }, { 1, 1 }, m_SmileTexture);
		m_Font->RenderText({ 0, 0 }, "Gröt");
		Renderer2D::End();

		Renderer2D::Begin(m_EditorCamera.Get());
		Renderer2D::End();
	}

}

