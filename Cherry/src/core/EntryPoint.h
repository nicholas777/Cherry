#pragma once

#include "../Events/EventListener.h"
#include "Application.h"

#ifdef CH_PLATFORM_WINDOWS

extern void Cherry::OnStart();
extern void Cherry::OnUpdate();
extern void Cherry::OnShutdown();

int main(int argc, char** argv) {
	Cherry::Application::InitEngine();
	Cherry::OnStart();

	void (*update)();
	update = &Cherry::OnUpdate;

	Cherry::Application::GetApplication().Run(update);

	Cherry::OnShutdown();
}

#endif