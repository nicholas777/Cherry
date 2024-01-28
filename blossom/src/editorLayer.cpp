#include "editorLayer.h"

#include "debug/profiler.h"
#include "scene/nativeScript.h"
#include "system/fileDialogs.h"

#include <entt/entt.hpp>
#include <imgui.h>

// BUG: Zooming doesn't zoom into the center of the screen, rather it zooms
// towards the bottom
// TODO: Support for gizoms rotating and scaling

namespace Cherry {
    Scoped<SceneHierarchyPanel> EditorLayer::m_SceneHierarchyPanel;
    Scoped<PropertiesPanel> EditorLayer::m_PropertiesPanel;
    Scoped<ContentBrowserPanel> EditorLayer::m_ContentBrowserPanel;

    Scene* EditorLayer::m_Scene = nullptr;
    Scene* EditorLayer::m_RuntimeScene = nullptr;
    std::string EditorLayer::m_ScenePath = "";
    EditorState EditorLayer::m_State = EditorState::None;
    bool EditorLayer::m_IsRuntime = false;
    std::string EditorLayer::m_ProjectPath{};

    Entity EditorLayer::m_SelectedEntity = Entity();

    std::vector<ReversableAction*> EditorLayer::m_ActionsToUndo = std::vector<ReversableAction*>();
    std::vector<ReversableAction*> EditorLayer::m_ActionsToRedo = std::vector<ReversableAction*>();

    Vector2f GetCameraOffsets(const Timestep& delta) {
        float x = 0, y = 0;

        if (Input::GetKeyPressed(Key::W)) {
            y -= 0.01f;
        }
        if (Input::GetKeyPressed(Key::S)) {
            y += 0.01f;
        }
        if (Input::GetKeyPressed(Key::A)) {
            x += 0.01f;
        }
        if (Input::GetKeyPressed(Key::D)) {
            x -= 0.01f;
        }

        return Vector2f(x * delta.GetMilliseconds(), y * delta.GetMilliseconds());
    }

    class CameraControllerScript : public NativeScript
    {
    public:
        void OnCreate() {}

        void OnUpdate(const Timestep& delta) {
            float x = 0, y = 0;

            if (Input::GetKeyPressed(Key::W)) {
                y += 0.01f;
            }
            if (Input::GetKeyPressed(Key::S)) {
                y -= 0.01f;
            }
            if (Input::GetKeyPressed(Key::A)) {
                x -= 0.01f;
            }
            if (Input::GetKeyPressed(Key::D)) {
                x += 0.01f;
            }

            if (!(x == 0 && y == 0)) {
                GetComponent<TransformComponent>().Translation +=
                    Vector2f(-x * delta.GetMilliseconds(), -y * delta.GetMilliseconds());
            }
        }

        void OnDestroy() {}
    };

    EditorLayer::~EditorLayer() {}

    void EditorLayer::OnAttach() {
        CH_PROFILE_FUNC();

        m_ProjectPath = "assets/Project";
        m_ContentBrowserPanel = new ContentBrowserPanel("assets/Project");

        m_ScenePath = "";
        m_Scene = new Scene;
        m_RuntimeScene = new Scene;
        m_State = EditorState::Edit;

        m_PlayButton = Texture::Create("assets/PlayButton.png");
        m_PauseButton = Texture::Create("assets/PauseButton.png");

        FramebufferData data;
        data.width = WINDOW_WIDTH;
        data.height = WINDOW_HEIGHT;
        data.attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RedInteger,
                             FramebufferTextureFormat::Depth24Stencil8 };

        m_Framebuffer = Framebuffer::Create(data);

        m_EditorCamera = StaticCamera(20, -1, 1);

        m_SceneHierarchyPanel = new SceneHierarchyPanel(m_Scene);
        m_PropertiesPanel = new PropertiesPanel();

        // Gizmos

        m_RedArrow = Texture::Create("assets/RedArrow.png");
        m_GreenArrow = Texture::Create("assets/GreenArrow.png");

        RenderCommand::SetClearColor({ 1, 0, 0, 1 });
    }

    void EditorLayer::OnDetach() {
        m_ContentBrowserPanel.Free();
    }

    void EditorLayer::OnUpdate(const Timestep& delta) {
        CH_PROFILE_FUNC();

        m_Framebuffer->Bind();
        if (m_IsRuntime) {
            m_RuntimeScene->OnUpdate(delta);
        } else {
            Vector2f xy = GetCameraOffsets(delta);
            Vector2f correction = m_EditorCamera.GetTransformCorrection();
            Translate(&m_EditorCamera.GetTransform(), xy.x, xy.y);

            Matrix4x4f mat = m_EditorCamera.GetTransform();
            Translate(&mat, correction.x, correction.y);

            m_Scene->OnUpdate(delta, mat, m_EditorCamera.GetProjection());

            // Gizmos
            if (m_SelectedEntity && !m_IsRuntime &&
                m_SelectedEntity.HasComponent<TransformComponent>()) {
                TransformComponent& tc = m_SelectedEntity.GetComponent<TransformComponent>();
                Matrix4x4f transform = Matrix4x4f::Identity();
                Translate(&transform, tc.Translation.x, tc.Translation.y);

                Renderer2D::Begin(m_EditorCamera.GetProjection(), m_EditorCamera.GetTransform());

                Translate(&transform, 0.75f, 0);
                Renderer2D::DrawRect(transform, m_RedArrow, { 1, 1, 1, 1 }, -1);

                Translate(&transform, -0.75f, 0.75f);
                Rotate(&transform, -90);
                Renderer2D::DrawRect(transform, m_GreenArrow, { 1, 1, 1, 1 }, -2);

                Renderer2D::End();
            }
        }

        if (m_EntitySelected) {
            auto [mouseX, mouseY] = ImGui::GetMousePos();
            mouseX -= m_ViewportPanelPos.x;
            mouseY -= m_ViewportPanelPos.y;

            mouseY = m_ViewportPanelSize.y - mouseY;

            m_Framebuffer->Bind();
            int id = m_Framebuffer->ReadPixel(1, (uint32_t)mouseX, (uint32_t)mouseY);
            m_Framebuffer->Unbind();

            // TODO: Renderer2D::RenderRect() defaults entityID parameter to -1
            // which in editor activates gizmos
            if (id == -1 || id == -2 && m_SelectedEntity) {
                m_GizmoType = id;
                m_GizmoSelected = true;
                m_GizmoStart = Vector2i(mouseX, mouseY);
                m_GizmoOffset = Vector2i();
                m_EntitySelected = false;

                m_GizmosPrevTranslation =
                    m_SelectedEntity.GetComponent<TransformComponent>().Translation;

                return;
            }

            Entity entity = Entity((entt::entity)id, m_Scene);
            m_EntitySelected = false;
            if (!entity.IsValid())
                return;

            SelectEntity(entity);
        }

        m_Framebuffer->Unbind();
    }

    void EditorLayer::OnEvent(const Event& e) {
        CH_PROFILE_FUNC();

        if (e.Type == EventType::KeyPressEvent) {
            const KeyPressEvent& event = static_cast<const KeyPressEvent&>(e);

            if (event.Keycode == Key::Z) {
                if (Input::GetKeyPressed(Key::Control)) {
                    UndoAction();
                }
            } else if (event.Keycode == Key::Y) {
                if (Input::GetKeyPressed(Key::Control)) {
                    RedoAction();
                }
            } else if (event.Keycode == Key::S) {
                if (Input::GetKeyPressed(Key::Control) && Input::GetKeyPressed(Key::Shift)) {
                    SaveFileAs();
                } else if (Input::GetKeyPressed(Key::Control)) {
                    SaveFile();
                }
            } else if (event.Keycode == Key::O) {
                if (Input::GetKeyPressed(Key::Control)) {
                    OpenFile();
                }
            } else if (event.Keycode == Key::R) {
                if (Input::GetKeyPressed(Key::Control)) {
                    if (Input::GetKeyPressed(Key::Shift) && !m_IsRuntime)
                        ScriptEngine::ReloadScripts();
                    else
                        ReloadAssets();
                }
            }
        }

        else if (e.Type == EventType::MouseScrollEvent) {
            const MouseScrollEvent& ev = static_cast<const MouseScrollEvent&>(e);
            if (!m_IsRuntime) {
                // TODO: When scrolling the diection reverses at some point
                Scale(&m_EditorCamera.GetTransform(), (float)ev.Offset / 25);
            }
        }

        else if (e.Type == EventType::MouseClickEvent) {
            m_EntitySelected = true;
        }

        else if (e.Type == EventType::MouseReleaseEvent) {
            if (!m_GizmoSelected)
                return;

            m_GizmoSelected = false;
            auto& transform = m_SelectedEntity.GetComponent<TransformComponent>();

            auto action = new TransformComponentEditAction();
            action->entity = m_SelectedEntity;

            action->oldPos = m_GizmosPrevTranslation;
            action->newPos = transform.Translation;

            action->oldRot = transform.Rotation;
            action->newRot = transform.Rotation;

            action->oldSize = transform.Scale;
            action->newSize = transform.Scale;

            RegisterAction(action);
        }

        else if (e.Type == EventType::MouseMoveEvent) {
            if (!m_GizmoSelected)
                return;

            auto [mouseX, mouseY] = ImGui::GetMousePos();

            mouseX -= m_ViewportPanelPos.x;
            mouseY -= m_ViewportPanelPos.y;

            mouseY = m_ViewportPanelSize.y - mouseY;

            m_GizmoOffset = m_GizmoStart - Vector2i(mouseX, mouseY);

            if (m_GizmoType == -1)
                m_SelectedEntity.GetComponent<TransformComponent>().Translation -=
                    Vector2f((float)(m_GizmoOffset.x / 20.0), 0);
            if (m_GizmoType == -2)
                m_SelectedEntity.GetComponent<TransformComponent>().Translation -=
                    Vector2f(0, (float)(m_GizmoOffset.y / 20.0));

            m_GizmoStart = Vector2i(mouseX, mouseY);
        }
    }

    void EditorLayer::OnImGuiRender() {
        CH_PROFILE_FUNC();
        static bool IsOpen = true;
        static bool opt_fullscreen = true;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen) {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        } else {
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
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGui::DockSpace(ImGui::GetID("MyDockSpace"), ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New Scene", "Ctrl+N")) {
                    NewFile();
                }
                if (ImGui::MenuItem("Open Scene", "Ctrl+O")) {
                    OpenFile();
                }
                if (ImGui::MenuItem("Save Scene", "Ctrl+S")) {
                    SaveFile();
                }
                if (ImGui::MenuItem("Save Scene As", "Ctrl+Shift+S")) {
                    SaveFileAs();
                }

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        m_SceneHierarchyPanel->OnUpdate();
        m_PropertiesPanel->OnUpdate(m_IsRuntime);
        m_ContentBrowserPanel->OnUpdate();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });

        ImGui::Begin("Scene bar", &IsOpen, ImGuiWindowFlags_NoTitleBar);
        if (ImGui::Button("Play")) {
            m_IsRuntime = !m_IsRuntime;
        }
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip("Play scene");
        }

        ImGui::SameLine();

        if (ImGui::Button("Reload")) {
            m_ContentBrowserPanel->WriteAssetmap();
            m_ContentBrowserPanel->SetDirectory("assets/Project");
        }
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip("Save and reload assets");
        }

        ImGui::End();

        ImGui::Begin("Scene Viewport");
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        ImVec2 viewportPos = ImGui::GetWindowContentRegionMin();
        ImVec2 viewportOffset = ImGui::GetWindowPos();

        m_ViewportPanelPos = { viewportPos.x + viewportOffset.x, viewportPos.y + viewportOffset.y };

        if (m_ViewportPanelSize != Vector2f(viewportSize.x, viewportSize.y)) {
            m_ViewportPanelSize = { viewportSize.x, viewportSize.y };
            m_Framebuffer->Resize(m_ViewportPanelSize);
        }

        uint32_t textureID = m_Framebuffer->GetColorAttachmentID(0);
        ImGui::Image((void*)textureID, viewportSize, ImVec2(0, 1), ImVec2(1, 0));

        ImGui::PopStyleVar();

        ImGui::ShowDemoWindow();

        ImGui::End();
        ImGui::End();
    }

    void EditorLayer::SelectEntity(const Entity& entity) {
        m_SelectedEntity = entity;
        m_PropertiesPanel->SetEntity(entity);
    }

    void EditorLayer::SelectAsset(Asset* asset) {
        m_PropertiesPanel->SetAsset(asset);
    }

    void EditorLayer::SelectScene(Scene* asset, const std::string& path) {
        m_Scene = asset;
        m_SceneHierarchyPanel->SetScene(asset);
        m_ScenePath = path;
    }

    void EditorLayer::RegisterAction(ReversableAction* action) {
        if (m_ActionsToUndo.size() >= 10) {
            delete *m_ActionsToUndo.begin();
            m_ActionsToUndo.erase(m_ActionsToUndo.begin());
            m_ActionsToUndo.push_back(action);
        } else {
            m_ActionsToUndo.push_back(action);
        }
    }

    void EditorLayer::UndoAction() {
        if (m_ActionsToUndo.size() > 0) {
            m_ActionsToUndo.back()->Reverse();

            if (m_ActionsToUndo.back()->IsEntityCreateAction) {
                EntityDeleteAction* reversed = new EntityDeleteAction;

                Entity entity = static_cast<EntityCreateAction*>(m_ActionsToUndo.back())->entity;

                reversed->entity = entity;

                if (entity.HasComponent<NameComponent>())
                    reversed->name = new NameComponent(entity.GetComponent<NameComponent>());

                if (entity.HasComponent<TransformComponent>())
                    reversed->transform =
                        new TransformComponent(entity.GetComponent<TransformComponent>());

                if (entity.HasComponent<SpriteComponent>())
                    reversed->sprite = new SpriteComponent(entity.GetComponent<SpriteComponent>());

                if (entity.HasComponent<CameraComponent>())
                    reversed->camera = new CameraComponent(entity.GetComponent<CameraComponent>());

                m_ActionsToRedo.push_back(reversed);
            } else {
                ReversableAction* reversed = m_ActionsToUndo.back()->ToReversed();
                m_ActionsToRedo.push_back(reversed);
            }

            m_ActionsToUndo.pop_back();
        }
    }

    void EditorLayer::RedoAction() {
        if (m_ActionsToRedo.size() > 0) {
            ReversableAction* reversed = m_ActionsToRedo.back()->ToReversed();
            m_ActionsToRedo.back()->Reverse();
            m_ActionsToRedo.pop_back();
            m_ActionsToUndo.push_back(reversed);
        }
    }

    void EditorLayer::NewFile() {
        m_Scene = new Scene();
        m_SceneHierarchyPanel->SetScene(m_Scene);
        m_ScenePath = "";
    }

    void EditorLayer::OpenFile() {
        std::filesystem::path path = FileDialogManager::OpenFile("Cherry Scene (.chs)\0*.chs\0\0)");

        if (!path.empty()) {
            if (path.extension() != ".chs") {
                CH_ERROR("Could not open file, not a Scene");
                return;
            }

            m_ScenePath = path.string();
            m_Scene = SceneSerializer::Deserialize(m_ScenePath);
            m_SceneHierarchyPanel->SetScene(m_Scene);
        }
    }

    void EditorLayer::SaveFile() {
        if (m_ScenePath.empty())
            SaveFileAs();
        else
            SceneSerializer::Serialize(m_Scene, m_ScenePath);
    }

    void EditorLayer::SaveFileAs() {
        std::filesystem::path path = FileDialogManager::SaveFile("Cherry Scene (.chs)\0*.chs\0\0)");
        m_ScenePath = path.string();

        if (path.extension() != ".chs") {
            CH_ERROR("File is not a .chs file");
        }

        SceneSerializer::Serialize(m_Scene, m_ScenePath);
    }


    void EditorLayer::ReloadAssets() {
        // TODO: Implement this
    }

} // namespace Cherry
