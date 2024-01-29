#pragma once

#include "application.h"
#include "debug/profiler.h"

extern Cherry::Application* Cherry::CreateApplication();

int main(int argc, char** argv) {
    Cherry::Profiler::BeginSession("Startup");
    auto app = Cherry::CreateApplication();
    app->Startup(argc, argv);
    Cherry::Profiler::EndSession();

    Cherry::Profiler::BeginSession("Runtime");
    app->Run();

    delete app;
    Cherry::Profiler::EndSession();
}
