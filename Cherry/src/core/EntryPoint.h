#pragma once

#include "../Events/EventListener.h"
#include "Application.h"

#ifdef CH_PLATFORM_WINDOWS

extern Cherry::Application* Cherry::CreateApplication();

int main(int argc, char** argv) {
	auto app = Cherry::CreateApplication();

	app->Run();

	delete app;
}

#endif