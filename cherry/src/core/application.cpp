#include "application.h"

#include "debug/profiler.h"
#include "epch.h"
#include "events/eventListener.h"
#include "events/eventType.h"
#include "events/input.h"
#include "platform/windows/windowsInput.h"
#include "renderer/renderCommand.h"
#include "renderer/renderer2D.h"
#include "scripting/scriptEngine.h"
#include "timestep.h"

namespace Cherry {
    // TODO: Fix warnings
    Application* Application::s_Application;

    Application::Application() {
        CH_PROFILE_FUNC();

        Configuration = ApplicationConfig();
        m_LayerStack = new LayerStack;

        m_ImGuiRenderer = new ImGuiRenderer;

        s_Application = this;
    }

    Application::~Application() {
        CH_PROFILE_FUNC();
        delete m_LayerStack;
        delete m_Window;
        Renderer2D::Shutdown();
    }

    void Application::Startup(int argc, char** argv) {
        CH_PROFILE_FUNC();

        Configuration.argc = argc;
        Configuration.argv = argv;

        m_Running = true;

        Log::Init(Configuration.Name);
        EventListener::InitEventListenerSystem();

        ScriptEngine::Init();

        m_Window = Window::Create({ Configuration.WindowWidth, Configuration.WindowHeight,
                                    Configuration.WindowTitle, Configuration.IsVSync });
        Renderer2D::Init();
        RenderCommand::Init();

        Input::Init();

        m_ImGuiRenderer->OnInit();

        for (auto layer: *m_LayerStack) { layer->OnAttach(); }

        RenderCommand::Init();
    }

    void Application::Run() {
        CH_PROFILE_FUNC();

        Timestep DeltaTime;

        while (m_Running) {
            float time = (float)m_Window->GetTime();
            DeltaTime = Timestep(time - m_LastFrame);
            m_LastFrame = time;

            m_Window->OnUpdate();

            for (Layer* layer: *m_LayerStack) layer->OnUpdate(DeltaTime);

            m_ImGuiRenderer->Begin();
            for (Layer* layer: *m_LayerStack) layer->OnImGuiRender();
            m_ImGuiRenderer->End();
        }

        m_ImGuiRenderer->OnShutdown();
        delete m_ImGuiRenderer;
    }

    void Application::OnEvent(const Event& e) {
        CH_PROFILE_FUNC();
        for (auto listener: EventListener::EventListeners[e.Type]) {
            listener->OnEvent(e);

            if (e.handled)
                break;
        }

        for (auto it = (*m_LayerStack).end(); it != (*m_LayerStack).begin();) {
            (**--it).OnEvent(e);

            if (e.handled)
                break;
        }
    }

    void Application::OnWindowResize(int width, int height) {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Application::OnWindowClose() {
        m_Running = false;
    }

    Application& Application::GetApplication() {
        return *s_Application;
    }

    Window* Application::GetWindow() {
        return m_Window;
    }
}
