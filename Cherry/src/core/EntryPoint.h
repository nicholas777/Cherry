#pragma once

#include "Application.h"
#include "Debug/Profiler.h"

#ifdef CH_PLATFORM_WINDOWS

extern Cherry::Application* Cherry::CreateApplication();

int main(int argc, char** argv) 
{
	Cherry::Profiler::BeginSession("Startup");
	auto app = Cherry::CreateApplication();
	app->Startup();
	Cherry::Profiler::EndSession();

	Cherry::Profiler::BeginSession("Runtime");
	app->Run();

	delete app;
	Cherry::Profiler::EndSession();
}

#endif