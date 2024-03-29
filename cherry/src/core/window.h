#pragma once

namespace Cherry
{
    struct WindowData
    {
        unsigned int Width, Height;
        std::string Title;
        bool VSync;

        WindowData(int width, int height, std::string title, bool vsync)
            : Width(width), Height(height), Title(title), VSync(vsync) {};

        WindowData()
            : Width(600), Height(400), Title("Game"), VSync(true) {};
    };

    class Window
    {
    public:
        virtual ~Window() {};

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetVSync(bool vsync) = 0;
        virtual bool IsVSync() const = 0;

        virtual double GetTime() = 0;

        virtual void OnUpdate() = 0;
        virtual void OnResize(int, int) = 0;

        virtual void* GetNativeWindow() = 0;
        virtual WindowData GetData() = 0;

        static Window* Create(WindowData data = WindowData());
    };
}
