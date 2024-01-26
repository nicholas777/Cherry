#pragma once

#include "events/event.h"
#include "imgui/imGuiRenderer.h"
#include "layerStack.h"
#include "window.h"

namespace Cherry {
#define WINDOW_WIDTH  (float)Application::GetApplication().GetWindow()->GetWidth()
#define WINDOW_HEIGHT (float)Application::GetApplication().GetWindow()->GetHeight()

    class Application
    {
    public:
        struct ApplicationConfig {
            int WindowWidth = 600, WindowHeight = 400;
            std::string WindowTitle;
            bool IsVSync = true;

            std::string Name = "App";
        };

    public:
        Application();
        virtual ~Application();

        LayerStack& GetLayerStack() { return *m_LayerStack; };

        void PushLayer(Layer* layer) { m_LayerStack->PushLayer(layer); };

        void Startup();
        void Run();

        void OnEvent(const Event& e);
        void OnWindowClose();
        void OnWindowResize(int width, int height);

        static Application& GetApplication();
        Window* GetWindow();

    protected:
        ApplicationConfig Configuration;
    private:
        static Cherry::Application* s_Application;

        bool m_Running;
        LayerStack* m_LayerStack;
        Window* m_Window;

        ImGuiRenderer* m_ImGuiRenderer;

        float m_LastFrame = 0.0f;
    };

    // Defined by client
    Application* CreateApplication();
}
