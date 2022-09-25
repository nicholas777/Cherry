#include "EditorLayer.h"
#include "System/FileDialogs.h"

namespace Cherry
{
	Scoped<SceneHierarchyPanel> EditorLayer::m_SceneHierarchyPanel;
	Scoped<PropertiesPanel> EditorLayer::m_PropertiesPanel;
	Scoped<ContentBrowserPanel> EditorLayer::m_ContentBrowserPanel;
	Shared<Scene> EditorLayer::m_Scene = Shared<Scene>(nullptr);
	Entity EditorLayer::m_SelectedEntity = Entity();

	std::vector<ReversableAction*> EditorLayer::m_ActionsToUndo = std::vector<ReversableAction*>();
	std::vector<ReversableAction*> EditorLayer::m_ActionsToRedo = std::vector<ReversableAction*>();

	Vector2f GetCameraOffsets(const Timestep& delta)
	{
		float x = 0, y = 0;

		if (Input::GetKeyPressed(Key::W))
		{
			y -= 0.01f;
		}
		if (Input::GetKeyPressed(Key::S))
		{
			y += 0.01f;
		}
		if (Input::GetKeyPressed(Key::A))
		{
			x += 0.01f;
		}
		if (Input::GetKeyPressed(Key::D))
		{
			x -= 0.01f;
		}

		return Vector2f(x * delta.GetMilliseconds(), y * delta.GetMilliseconds());
	}

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
		m_ContentBrowserPanel = new ContentBrowserPanel("assets/Project");

		m_ScenePath = "";
		m_Scene = new Scene;

		FramebufferData data;
		data.width = WINDOW_WIDTH;
		data.height = WINDOW_HEIGHT;

		m_Framebuffer = Framebuffer::Create(data);

		m_EditorCamera = StaticCamera(5, -1, 1);

		m_SceneHierarchyPanel = new SceneHierarchyPanel(m_Scene);
		m_PropertiesPanel = new PropertiesPanel();

		RenderCommand::SetClearColor({1, 0, 0, 1});
	}

	void EditorLayer::OnDetach()
	{
		m_ContentBrowserPanel.Free();
	}

	void EditorLayer::OnUpdate(const Timestep& delta)
	{
		m_Framebuffer->Bind();
		if (m_IsRuntime)
		{
			m_Scene->OnUpdate(delta);
		}
		else
		{
			Vector2f xy = GetCameraOffsets(delta);
			Translate(&m_EditorCamera.GetTransform(), xy.x, xy.y);
			m_Scene->OnUpdate(delta, m_EditorCamera);
		}

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		if (e.Type == EventType::KeyPressEvent)
		{
			KeyPressEvent& event = static_cast<KeyPressEvent&>(e);

			if (event.Keycode == Key::Z)
			{
				if (Input::GetKeyPressed(Key::Control))
				{
					UndoAction();
				}
			}
			else if (event.Keycode == Key::Y)
			{
				if (Input::GetKeyPressed(Key::Control))
				{
					RedoAction();
				}
			}
		}

		if (e.Type == EventType::MouseScrollEvent)
		{
			MouseScrollEvent& ev = static_cast<MouseScrollEvent&>(e);
			if (!m_IsRuntime)
			{
				// TODO: When scrolling the diection reverses at some point
				Scale(&m_EditorCamera.GetTransform(), (float)ev.Offset / 25);
			}
		}
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

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New Scene", "Ctrl+N"))
				{
					NewFile();
				}
				if (ImGui::MenuItem("Open Scene", "Ctrl+O"))
				{
					OpenFile();
				}
				if (ImGui::MenuItem("Save Scene", "Ctrl+S"))
				{
					SaveFile();
				}
				if (ImGui::MenuItem("Save Scene As", "Ctrl+Shift+S"))
				{
					SaveFileAs();
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		m_SceneHierarchyPanel->OnUpdate();
		m_PropertiesPanel->OnUpdate();
		m_ContentBrowserPanel->OnUpdate();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });

		ImGui::Begin("Scene bar", &IsOpen, ImGuiWindowFlags_NoTitleBar);
		if (ImGui::Button("Play"))
		{
			m_IsRuntime = !m_IsRuntime;
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::SetTooltip("Play scene");
		}

		ImGui::SameLine();

		if (ImGui::Button("Reload"))
		{
			m_ContentBrowserPanel->WriteAssetmap();
			m_ContentBrowserPanel->SetDirectory("assets/Project");
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::SetTooltip("Save and reload assets");
		}


		ImGui::End();

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

		ImGui::ShowDemoWindow();

        ImGui::End();
		ImGui::End();
	}

	void EditorLayer::SelectEntity(const Entity& entity)
	{
		m_SelectedEntity = entity;
		m_PropertiesPanel->SetEntity(entity);
	}

	void EditorLayer::SelectAsset(Asset* asset)
	{
		m_PropertiesPanel->SetAsset(asset);
	}

	void EditorLayer::SelectScene(Shared<Scene> asset)
	{
		m_Scene = asset;
		m_SceneHierarchyPanel->SetScene(asset);
	}

	void EditorLayer::RegisterAction(ReversableAction* action)
	{
		if (m_ActionsToUndo.size() >= 10)
		{
			delete* m_ActionsToUndo.begin();
			m_ActionsToUndo.erase(m_ActionsToUndo.begin());
			m_ActionsToUndo.push_back(action);
		}
		else
		{
			m_ActionsToUndo.push_back(action);
		}
	}

	void EditorLayer::UndoAction()
	{
		if (m_ActionsToUndo.size() > 0)
		{
			m_ActionsToUndo.back()->Reverse();

			if (m_ActionsToUndo.back()->IsEntityCreateAction)
			{
				EntityDeleteAction* reversed = new EntityDeleteAction;

				Entity entity = static_cast<EntityCreateAction*>(m_ActionsToUndo.back())->entity;

				reversed->entity = entity;

				if (entity.HasComponent<NameComponent>())
					reversed->name = new NameComponent(entity.GetComponent<NameComponent>());

				if (entity.HasComponent<TransformComponent>())
					reversed->transform = new TransformComponent(entity.GetComponent<TransformComponent>());

				if (entity.HasComponent<SpriteComponent>())
					reversed->sprite = new SpriteComponent(entity.GetComponent<SpriteComponent>());

				if (entity.HasComponent<CameraComponent>())
					reversed->camera = new CameraComponent(entity.GetComponent<CameraComponent>());

				m_ActionsToRedo.push_back(reversed);
			}
			else
			{
				ReversableAction* reversed = m_ActionsToUndo.back()->ToReversed();
				m_ActionsToRedo.push_back(reversed);
			}

			m_ActionsToUndo.pop_back();
		}
	}
	
	void EditorLayer::RedoAction()
	{
		if (m_ActionsToRedo.size() > 0)
		{
			ReversableAction* reversed = m_ActionsToRedo.back()->ToReversed();
			m_ActionsToRedo.back()->Reverse();
			m_ActionsToRedo.pop_back();
			m_ActionsToUndo.push_back(reversed);
		}
	}

	void EditorLayer::NewFile()
	{
		m_Scene = new Scene();
		m_SceneHierarchyPanel->SetScene(m_Scene);
		m_ScenePath = "";
	}

	void EditorLayer::OpenFile()
	{
		std::filesystem::path path = FileDialogManager::OpenFile("Cherry Scene (.chs)\0*.chs\0\0)");

		if (!path.empty())
		{
			if (path.extension() != ".chs")
			{
				CH_ERROR("Could not open file, not a Scene");
				return;
			}

			m_ScenePath = path;
			m_Scene = SceneSerializer::Deserialize(path.string());
			m_SceneHierarchyPanel->SetScene(m_Scene);
		}
	}

	void EditorLayer::SaveFile()
	{
		if (m_ScenePath.empty())
			SaveFileAs();
		else
			SceneSerializer::Serialize(m_Scene, m_ScenePath.string());
	}

	void EditorLayer::SaveFileAs()
	{
		std::filesystem::path path = FileDialogManager::SaveFile("Cherry Scene (.chs)\0*.chs\0\0)");
		m_ScenePath = path;

		if (path.extension() != ".chs")
		{
			CH_ERROR("File is not a .chs file");
		}

		SceneSerializer::Serialize(m_Scene, m_ScenePath.string());
	}

}
