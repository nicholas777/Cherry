#include "EditorLayer.h"

namespace Cherry
{
	Scoped<SceneHierarchyPanel> EditorLayer::m_SceneHierarchyPanel;
	Scoped<PropertiesPanel> EditorLayer::m_PropertiesPanel;

	class CameraControllerScript : public Script
	{
	public:
		void OnCreate()
		{

		}

		void OnUpdate(const Timestep& delta)
		{
			float x = 0, y = 0;

			if (Input::GetKeyPressed(Key::W))
			{
				y += 0.01f;
			}
			if (Input::GetKeyPressed(Key::S))
			{
				y -= 0.01f;
			}
			if (Input::GetKeyPressed(Key::A))
			{
				x -= 0.01f;
			}
			if (Input::GetKeyPressed(Key::D))
			{
				x += 0.01f;
			}

			if (!(x == 0 && y == 0))
			{
				GetComponent<TransformComponent>().Translation += Vector2f(-x * delta.GetMilliseconds(), -y * delta.GetMilliseconds());
			}
		}

		void OnDestroy()
		{

		}
	};

	EditorLayer::~EditorLayer()
	{
	}

	void EditorLayer::OnAttach()
	{
		m_Scene = new Scene;

		FramebufferData data;
		data.width = WINDOW_WIDTH;
		data.height = WINDOW_HEIGHT;

		m_Framebuffer = Framebuffer::Create(data);

		Entity e = m_Scene->CreateEntity("Smiley");

		TextureParams params;
		params.format = TextureFormat::Auto;
		params.minFilter = TextureFilter::Linear;
		params.magFilter = TextureFilter::Nearest;
		params.wrap = TextureWrap::Repeat;

		m_SmileTexture = Texture::Create("assets/Smile.png", params);
		e.AddComponent<SpriteComponent>();
		e.GetComponent<SpriteComponent>().SpriteTexture = m_SmileTexture.Get();
		e.AddComponent<TransformComponent>(Vector2f(0, 0), 0.0f, Vector2f(1, 1));
		
		float aspect = WINDOW_WIDTH / WINDOW_HEIGHT;
		
		m_EditorCamera = m_Scene->CreateEntity("Main camera");
		m_EditorCamera.AddComponent<TransformComponent>(
			Vector2f(0.0f, 0.0f), 
			0.0f, 
			Vector2f(1.0f, 1.0f)
		);

		m_EditorCamera.AddComponent<CameraComponent>();
		m_EditorCamera.GetComponent<CameraComponent>().camera = Camera(ortho(-12, 12, 10, -10));

		m_EditorCamera.AddComponent<ScriptComponent>().Bind<CameraControllerScript>();

		m_Font = new Font("assets/Goldfish.ttf", 64);

		m_SceneHierarchyPanel = new SceneHierarchyPanel(m_Scene);
		m_PropertiesPanel = new PropertiesPanel();

		RenderCommand::SetClearColor({1, 0, 0, 1});
	}

	void EditorLayer::OnUpdate(const Timestep& delta)
	{
		m_Framebuffer->Bind();
		m_Scene->OnUpdate(delta);
		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		static bool IsOpen = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::Begin("DockSpace Demo", &IsOpen, window_flags);

        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGui::DockSpace(ImGui::GetID("MyDockSpace"), ImVec2(0.0f, 0.0f), dockspace_flags);
        }

		m_SceneHierarchyPanel->OnUpdate();
		m_PropertiesPanel->OnUpdate();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Scene Viewport");
		ImVec2 viewportSize = ImGui::GetContentRegionAvail();
		
		if (m_ViewportPanelSize != Vector2f(viewportSize.x, viewportSize.y))
		{
			m_ViewportPanelSize = { viewportSize.x, viewportSize.y };
			m_Framebuffer->Resize(m_ViewportPanelSize);
		}

		uint32_t textureID = m_Framebuffer->GetColorAttachment();
		ImGui::Image((void*)textureID, viewportSize, ImVec2(0, 1), ImVec2(1, 0));

		ImGui::PopStyleVar();

        ImGui::End();
        ImGui::End();
	}

	void EditorLayer::SelectEntity(const Entity& entity)
	{
		CH_INFO("Entity selected: " + entity.GetComponent<NameComponent>().Name);
		m_PropertiesPanel->SetEntity(entity);
	}

}

