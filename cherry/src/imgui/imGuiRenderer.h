#pragma once

namespace Cherry {
    class ImGuiRenderer
    {
    public:
        ImGuiRenderer() {}

        ~ImGuiRenderer() {}

        void OnInit();
        void OnShutdown();

        void Begin();
        void End();
    };
}
